type t;
type underlyingSink('chunk, 'controller) = {
  start: option('controller => Js.Promise.t(unit)),
  write: option(('chunk, 'controller) => Js.Promise.t(unit)),
  close: option(unit => Js.Promise.t(unit)),
  abort: option(string => Js.Promise.t(unit)),
};

type queuingStrategy('a) = {
  highWaterMark: option(int),
  size: option('a => int),
};

module DefaultWriter = {
  type t;

  [@bs.get] external desiredSize: t => option(int) = "desiredSize";
  [@bs.get] external closed: t => Js.Promise.t(unit) = "closed";
  [@bs.get] external ready: t => Js.Promise.t(unit) = "ready";
  [@bs.send.pipe: t] external abort: string => Js.Promise.t(unit) = "abort";
  [@bs.send.pipe: t] external close: unit => Js.Promise.t(unit) = "close";
  [@bs.send.pipe: t] external releaseLock: unit => unit = "releaseLock";
  [@bs.send.pipe: t] external write: 'a => Js.Promise.t(unit) = "write";
};

[@bs.module "web-streams-polyfill/es2018"] [@bs.new]
external make: underlyingSink('a, 'b) => t = "WritableStream";

[@bs.send.pipe: t] external getWriter: unit => DefaultWriter.t = "getWriter";
[@bs.send.pipe: t] external close: unit => Js.Promise.t(unit) = "close";
[@bs.send.pipe: t] external abort: string => Js.Promise.t(unit) = "abort";
