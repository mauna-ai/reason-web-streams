module DefaultReader = ReadableStream_DefaultReader;

type t;
type signal;
type getReaderMode = {mode: string};
type pipeThroughArgs = {
  writable: WritableStream.t,
  t,
};
type pipeOptions = {
  preventClose: option(bool),
  preventAbort: option(bool),
  preventCancel: option(bool),
  signal: option(signal),
};
type asyncIterator;
type iterator = {preventCancel: option(bool)};

[@bs.module "web-streams-polyfill/es2018"] [@bs.new]
external make: unit => t = "ReadableStream";

[@bs.send.pipe: t] external cancel: 'a => Js.Promise.t(unit) = "cancel";
[@bs.send.pipe: t] external getReader: 'a => DefaultReader.t = "getReader";
[@bs.send.pipe: t]
external pipeThrough: (pipeThroughArgs, pipeOptions) => WritableStream.t =
  "pipeThrough";
[@bs.send.pipe: t]
external pipeTo: (WritableStream.t, pipeOptions) => Js.Promise.t(unit) =
  "pipeTo";
[@bs.send.pipe: t] external tee: unit => (t, t) = "tee";
[@bs.send.pipe: t]
external getIterator: iterator => asyncIterator = "getIterator";
