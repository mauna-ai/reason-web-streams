type t;

[@bs.send.pipe: t] external cancel: 'a => Js.Promise.t(unit) = "cancel";
[@bs.send.pipe: t] external read: 'a => 'b = "read";
