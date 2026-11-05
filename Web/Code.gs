// Set constants in Const.gs

/**
 * Entry point. The script runs when its requested via http GET
 */
function doGet(){
  const output = GetEvents();
  return ContentService.createTextOutput(JSON.stringify(output))
    .setMimeType(ContentService.MimeType.JSON);
}

/**
 * Main function to get all the calendar events and sort them into the max number of lines per each grouping:
 * TODAY, LATER, NEXT
 * 
 * Outputs json object to be parsed by arduino
 */
function GetEvents(){
  /// SETUP
  const now = new Date();
  now.setHours(0, 0, 0, 0);

  // Retrieve calendar by ID (preferred) or by name as fallback
  let cal = null;
  if (typeof CAL_ID !== 'undefined' && CAL_ID && CAL_ID.trim().length > 0) {
    cal = CalendarApp.getCalendarById(CAL_ID.trim());
  }

  if (!cal && typeof CAL_NAME !== 'undefined' && CAL_NAME && CAL_NAME.trim().length > 0) {
    const calendars = CalendarApp.getCalendarsByName(CAL_NAME.trim());
    if (calendars && calendars.length > 0) {
      cal = calendars[0];
    }
  }

  // If neither CAL_ID nor CAL_NAME resolved, try default calendar
  if (!cal) {
    cal = CalendarApp.getDefaultCalendar();
  }

  if (!cal) {
    const identifier = (typeof CAL_ID !== 'undefined' && CAL_ID) ? CAL_ID : (typeof CAL_NAME !== 'undefined' ? CAL_NAME : "default");
    return {
      error: "Calendar not found: " + identifier,
      date: now.toDateString().substring(0, now.toDateString().length - 5),
      today: ["Calendar not found: " + identifier]
    };
  }

  // Local phase counts for this execution to avoid state leakage across warm container instances
  const phaseCounts = {
    today: 0,
    later: 0,
    next: 0
  };

  /// CALCULATE weeks
  const nextWeek = new Date(now);
  nextWeek.setDate(now.getDate() + 7 - now.getDay());

  const later = new Date(now);
  later.setDate(now.getDate() + 14 - now.getDay());
  later.setHours(0, 0, 0, 0);

  /// GET EVENTS from the calendar
  const events = cal.getEvents(now, later);

  /// POPULATE the events into the JSON Object
  let output = {
    date: now.toDateString().substring(0, now.toDateString().length - 5),
    today: []
  };

  events.forEach((e) => {
    let eStartDate = e.getStartTime();
    let eEndDate = e.getEndTime();

    if (e.isAllDayEvent()) {
      eEndDate.setDate(eEndDate.getDate() - 1); // All day events end on 00:00 of the next day. 
    }
    
    let isMultiDay = (eStartDate.getDate() != eEndDate.getDate());
    const isMidMultiDay = isMultiDay && (eStartDate.getHours() !== 0 || eStartDate.getMinutes() !== 0);
    
    const eStartDateStr = (eStartDate.getDate() < 10 ? "0" : "") + eStartDate.getDate().toString() + " " 
          + eStartDate.toDateString().substring(0, 3);
    const title = ((e.isAllDayEvent() || isMultiDay) && !isMidMultiDay ? "" :  eStartDate.toLocaleTimeString("en-US", {hour12: false, timeStyle: "short"}) 
          + " ") + e.getTitle();
    const multiDayTitle = isMidMultiDay ? title.substring(6) : title;

    // Set hours and such to 0 on date times for all the day-level calculations now
    eStartDate.setHours(0, 0, 0, 0);
    eEndDate.setHours(0, 0, 0, 0);

    const eStartDateMultiStr = eStartDateStr + " - " + (eEndDate.getDate() < 10 ? "0" : "") + eEndDate.getDate().toString() + " " 
          + eEndDate.toDateString().substring(0, 3);
    
    if (eStartDate <= now) {
      // today
      pushEventToList(output, "today", eStartDateStr, title, phaseCounts);
      if (isMultiDay) {
        if (eEndDate > now) {
          // later
          pushEventToList(output, "later", eStartDateMultiStr, multiDayTitle, phaseCounts);
        }
        if (eEndDate >= nextWeek) {
          // next
          pushEventToList(output, "next", eStartDateMultiStr, multiDayTitle, phaseCounts);
        }
      }
    } else if (eStartDate < nextWeek) {
      // later
      if (isMultiDay && eEndDate >= nextWeek) {
          // next
          pushEventToList(output, "next", eStartDateMultiStr, multiDayTitle, phaseCounts);
      }

      pushEventToList(output, "later", isMultiDay ? eStartDateMultiStr : eStartDateStr, multiDayTitle, phaseCounts);
    } else {
      // next
      pushEventToList(output, "next", isMultiDay ? eStartDateMultiStr : eStartDateStr, multiDayTitle, phaseCounts);
    }

  });
  
  Logger.log(output);
  return output;
}

/**
 * Helper function to add events to the correct phase, keeping track of phase lines.
 */
function pushEventToList(output, phase, date, title, phaseCounts) {
  // Always add a count for title & two if multiline
  phaseCounts[phase]++;
  if (title.length > LINE_LEN) phaseCounts[phase]++;
  title = title.substring(0, 2 * LINE_LEN + 1);

  if (phase === "today") {
    // today is an array of titles
    if (phaseCounts.today < ALLOWED_LINES) {
      output.today.push(title);
    } else {
      output.today_left = (output.today_left || 0) + 1;
    }
  } else {
    // later and next are objects of date arrays
    if (typeof output[phase] === "undefined") {
      output[phase] = {};
    }
    if (typeof output[phase][date] === "undefined") {
      phaseCounts[phase]++;
      if (phaseCounts[phase] < ALLOWED_LINES) {
        output[phase][date] = [];
      }
    }

    if (phaseCounts[phase] < ALLOWED_LINES) {
      output[phase][date].push(title);
    } else {
      output[phase]["left"] = (output[phase]["left"] || 0) + 1;
    }
  }
}