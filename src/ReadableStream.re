module DefaultController = {
  type t = {desiredSize: int};

  [@bs.send] external close: t => unit = "close";
  [@bs.send] external enqueue: 'a => unit = "enqueue";
  [@bs.send] external error: 'a => unit = "error";
};

module DefaultReader = {
  type t;

  [@bs.send] external cancel: (t, 'a) => Js.Promise.t(unit) = "cancel";
  [@bs.send] external read: (t, 'a) => 'b = "read";
};

type status;
type either('a, 'b) =
  | Left('a)
  | Right('b);

type t('a) = either(Js.Promise.t('a), status);
type signal;
type getReaderMode = {mode: string};
type pipeThroughArgs('a) = {
  writable: WritableStream.t,
  t: t('a),
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
external _make: (underlyingSource('a), option(queuingStrategy('b))) => t('a) = "ReadableStream";

let make = (~underlyingSource, ~strategy, ()) => _make(underlyingSource, strategy);

[@bs.send.pipe: t('a)] external cancel: 'a => Js.Promise.t(unit) = "cancel";
[@bs.send] external getReader: (t('b), 'a) => DefaultReader.t = "getReader";
[@bs.send] external pipeThrough: (t('b), 'a) => t('a) = "pipeThrough";
[@bs.send] external pipeTo: (t('a), WritableStream.t, pipeOptions) => Js.Promise.t(unit) = "pipeTo";
[@bs.send] external tee: t('a) => (t('a), t('a)) = "tee";
[@bs.send] external getIterator: (t('a), iterator) => asyncIterator = "getIterator";