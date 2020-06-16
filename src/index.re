open ReadableStream;

let rs = make();
let reader = rs |> getReader();

Js.log(reader);
