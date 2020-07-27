module DefaultController = {
  type t = {desiredSize: int};

  [@bs.send] external close: t => unit = "close";
  [@bs.send] external enqueue: (t, 'a) => unit = "enqueue";
  [@bs.send] external error: 'a => unit = "error";
};

type readResult('a) = {
  done_: bool,
  value: option('a),
};

module DefaultReader = {
  type t;
  type chunk('a) = {
    [@bs.as "done"]
    _done: bool,
    value: 'a,
  };

  [@bs.send] external cancel: (t, 'a) => Js.Promise.t(unit) = "cancel";
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  [@bs.send] external read: t => Js.Promise.t(chunk('a)) = "read";
=======
  [@bs.send] external read: t => Js.Promise.t(readResult('a)) = "read";
  [@bs.send] external releaseLock: t => unit = "releaseLock";
>>>>>>> master
=======
  [@bs.send] external read: t => Js.Promise.t(readResult('a)) = "read";
  [@bs.send] external releaseLock: t => unit = "releaseLock";
>>>>>>> master
=======
  [@bs.send] external read: t => Js.Promise.t(readResult('a)) = "read";
  [@bs.send] external releaseLock: t => unit = "releaseLock";
>>>>>>> master
};

type status;
type either('a, 'b) =
  | Left('a)
  | Right('b);

type t;
type signal;
type getReaderMode = {mode: string};
type pipeThroughArgs('a) = {
  writable: WritableStream.t,
  t: t,
};
type pipeOptions = {
  preventClose: option(bool),
  preventAbort: option(bool),
  preventCancel: option(bool),
  signal: option(signal),
};
type asyncIterator;
type iterator = {preventCancel: option(bool)};

type underlyingSource('a) = {
  start: option(DefaultController.t => unit),
  pull: option(DefaultController.t => unit),
  cancel: option(DefaultController.t => unit),
  type_: option(string),
};

type queuingStrategy('a) = {
  highWaterMark: option(int),
  size: option('a => int),
};

[@bs.module "web-streams-polyfill/es2018"] [@bs.new]
external _make: (underlyingSource('a), option(queuingStrategy('b))) => t = "ReadableStream";

let make = (~underlyingSource, ~strategy, ()) => _make(underlyingSource, strategy);

[@bs.get] external locked: t => bool = "locked";
[@bs.send] external cancel: (t, 'a) => Js.Promise.t(unit) = "cancel";
[@bs.send] external getReader: t => DefaultReader.t = "getReader";
[@bs.send] external pipeThrough: (t, 'a) => t = "pipeThrough";
[@bs.send] external pipeTo: (t, WritableStream.t, pipeOptions) => Js.Promise.t(unit) = "pipeTo";
[@bs.send] external tee: t => (t, t) = "tee";
[@bs.send] external getIterator: (t, iterator) => asyncIterator = "getIterator";
