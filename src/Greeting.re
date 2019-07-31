[@react.component]
let make = (~name) =>
  <button> {React.string("Hello " ++ name ++ "!")} </button>;
