type t;

type transformer('controller, 'chunk) = {
  start: option('controller => Js.Promise.t(unit)),
  transformer: option(('chunk, 'controller) => Js.Promise.t(unit)),
  flush: option('controller => Js.Promise.t(unit)),
};

type queuingStrategy('a) = {
  highWaterMark: option(int),
  size: option('a => int),
};

[@bs.module "web-streams-polyfill/es2018"] [@bs.new]
external make:
  (transformer('a, 'b), queuingStrategy('b), queuingStrategy('b)) => t =
  "TransformStream";

[@bs.get] external readable: t => ReadableStream.t = "readable";
[@bs.get] external writable: t => WritableStream.t = "writable";
