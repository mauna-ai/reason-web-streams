type t = {locked: bool};

module DefaultController = {
  type t;
};

type underlyingSink('chunk) = {
  start: option(DefaultController.t => Js.Promise.t(unit)),
  write: option(('chunk, DefaultController.t) => Js.Promise.t(unit)),
  close: option(unit => Js.Promise.t(unit)),
  abort: option(string => Js.Promise.t(unit)),
  type_: option(string),
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
  [@bs.send] external abort: (t, string) => Js.Promise.t(unit) = "abort";
  [@bs.send] external close: (t, unit) => Js.Promise.t(unit) = "close";
  [@bs.send] external releaseLock: (t, unit) => unit = "releaseLock";
  [@bs.send] external write: (t, 'a) => Js.Promise.t(unit) = "write";
};

[@bs.module "web-streams-polyfill/es2018"] [@bs.new]
external _make:
  (option(underlyingSink('a)), option(queuingStrategy('b))) => t =
  "WritableStream";

let make = (~underlyingSink=?, ~strategy=?, ()) =>
  _make(underlyingSink, strategy);

[@bs.send] external getWriter: (t, unit) => DefaultWriter.t = "getWriter";
[@bs.send] external close: (t, unit) => Js.Promise.t(unit) = "close";
[@bs.send] external abort: (t, string) => Js.Promise.t(unit) = "abort";
