type t;

module DefaultController = {
  type t = {desiredSize: int};

  [@bs.send] external enqueue: (t, 'a) => unit = "enqueue";
  [@bs.send] external error: (t, 'a) => unit = "error";
  [@bs.send] external terminate: t => unit = "terminate";
};

type transformer('chunk) = {
  start: option(DefaultController.t => Js.Promise.t(unit)),
  transform: option(('chunk, DefaultController.t) => unit),
  flush: option(DefaultController.t => Js.Promise.t(unit)),
};

type queuingStrategy('a) = {
  highWaterMark: option(int),
  size: option('a => int),
};

[@bs.module "web-streams-polyfill/es2018"] [@bs.new]
external _make:
  (
    option(transformer('a)),
    option(queuingStrategy('b)),
    option(queuingStrategy('c))
  ) =>
  t =
  "TransformStream";

let make = (~transformer=?, ~writableStrategy=?, ~readableStrategy=?, ()) =>
  _make(transformer, writableStrategy, readableStrategy);

[@bs.get] external readable: t => ReadableStream.t('a) = "readable";
[@bs.get] external writable: t => WritableStream.t = "writable";
