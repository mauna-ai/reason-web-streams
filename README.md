# @mauna/reason-web-streams

![npm](https://img.shields.io/npm/v/@mauna/reason-web-streams)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


ReasonWebStreams is the Reason bindings for [web-streams-polyfill](https://github.com/MattiasBuelens/web-streams-polyfill).

## Install

```
npm i @mauna/reason-web-streams
```

Add it to `bsconfig.json`

```diff
  "bs-dependencies": [
+   "@mauna/reason-web-streams",
  ]
```

You can now use the **MaunaReasonWebStreams** module.

## Usage

```re
open MaunaReasonWebStreams

let underlyingSource: ReadableStream.underlyingSource('a) = {
  start: None,
  pull: None,
  cancel: None,
  type_: None,
};

let strategy: ReadableStream.queuingStrategy('a) = {
  highWaterMark: None,
  size: None,
};

let readable =
  ReadableStream.make(~underlyingSource, ~strategy=Some(strategy), ());

```
