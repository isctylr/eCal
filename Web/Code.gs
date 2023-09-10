// Set constants in Const.gs

/**
 * Entry point. The script runs when its requested via http GET
 */
function doGet(){
  //Logger.log(ContentService.createTextOutput(GetEvents()));
  const output = GetEvents();
  return ContentService.createTextOutput(JSON.stringify(output))
    .setMimeType(ContentService.MimeType.JSON);
}

let phaseCounts = {
  today: 0,
  later: 0,
  next: 0
};

/**
 * Main function to get all the calendar events and sort them into the max number of lines per each grouping:
 * TODAY, LATER, NEXT
 * 
 * Outputs json object to be parsed by arduino
 */
function GetEvents(){
  /// SETUP
  const cal = CalendarApp.getCalendarsByName(CAL_NAME)[0];
  const now = new Date();
  now.setHours(0, 0, 0, 0);

  /// CALCULATE weeks
  const nextWeek = new Date(now);
  nextWeek.setDate(now.getDate() + 7 - now.getDay());

  let later = new Date();
  later.setDate(now.getDate() + 14 - now.getDay());

  /// GET EVENTS from the calendar
  const events = cal.getEvents(now, later);

  /// POPULATE the events into the JSON Object
  let output = {
    date: now.toDateString().substring(0, now.toDateString().length - 5),
    today: [],
    // later: {},
    // next: {}
  };

  events.forEach((e,i) => {
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

    // Set hours and such to 0 on date times for all the day-level calculations now. Its just easier this way I swear
    eStartDate.setHours(0, 0, 0, 0);
    eEndDate.setHours(0, 0, 0, 0);

    const eStartDateMultiStr = eStartDateStr + " - " + (eEndDate.getDate() < 10 ? "0" : "") + eEndDate.getDate().toString() + " " 
          + eEndDate.toDateString().substring(0, 3);
    
    if (eStartDate <= now) {
      // today
      pushEventToList(output, "today", eStartDateStr, title);
      if (isMultiDay) {
        if (eEndDate > now) {
          // later
          pushEventToList(output, "later", eStartDateMultiStr, multiDayTitle);
        }
        if (eEndDate >= nextWeek) {
          // next
          pushEventToList(output, "next", eStartDateMultiStr, multiDayTitle);
        }
      }
    } else if (eStartDate < nextWeek) {
      // later
      if (isMultiDay && eEndDate >= nextWeek) {
          // next
          pushEventToList(output, "next", eStartDateMultiStr, multiDayTitle);
      }

      pushEventToList(output, "later", isMultiDay ? eStartDateMultiStr : eStartDateStr, multiDayTitle);
    } else {
      // next
      pushEventToList(output, "next", isMultiDay ? eStartDateMultiStr : eStartDateStr, multiDayTitle);
    }

  });
  
  Logger.log(output);
  return output;
}

/**
 * Helper function to add events to the correct phase, keeping track of phase lines. +1 to phase's "left" after ALLOWED_LINES cap
 */
function pushEventToList(output, phase, date, title) {
  // Always add a count for title & two if multiline
  phaseCounts[phase]++;
  if (title.length > LINE_LEN) phaseCounts[phase]++;
  title = title.substring(0, 2 * LINE_LEN + 1);

  if (phase === "today") {
    // today is just an array
    if (phaseCounts.today < ALLOWED_LINES) {
      output.today.push(title);
    } else if (typeof output.today["left"] === "undefined") {
      output.today["left"] = Number(1).toFixed(0);
    } else {
      output.today["left"]++;
    }
  } else {
    // later and next are objects of date arrays
    if (typeof output[phase] === "undefined") {
      // first event of phase, create phase in obj
      output[phase] = {};
    }
    if (typeof output[phase][date] === "undefined") {
      // first event with date, create date key and add to phase count
      phaseCounts[phase]++;
      if (phaseCounts[phase] < ALLOWED_LINES) {
        output[phase][date] = [];
      }
    }

    if (phaseCounts[phase] < ALLOWED_LINES) {
      output[phase][date].push(title);
    } else if (typeof output[phase]["left"] === "undefined") {
      output[phase]["left"] = Number(1).toFixed(0);
    } else {
      output[phase]["left"]++;
    }
  }
}