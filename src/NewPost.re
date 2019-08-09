open ReasonUrql;
module PostTweet = [%graphql
  {|
  mutation post($message: String, $author: String) {
    sendTweet(input: {message: $message, author: $author}) {
      tweet {
        message
      }
    }
  }
|}
];

[@react.component]
let make = (~refetch) => {
  let (username, updateUsername) = React.useState(() => "");
  let (text, updateText) = React.useState(() => "");

  let (_, executePost) =
    Hooks.useMutation(
      ~request=PostTweet.make(~message=text, ~author=username, ()),
    );

  let handle = (cb, event) => {
    let value = ReactEvent.Form.target(event)##value;
    cb(_ => value);
  };

  let onClick = _ => {
    executePost() |> ignore;
    refetch();
    updateText(_ => "");
  };
  <div>
    {React.string("Username:")}
    <input type_="text" onChange={handle(updateUsername)} value=username />
    <br />
    <textarea onChange={handle(updateText)} value=text />
    <br />
    <button onClick> {React.string("Post")} </button>
  </div>;
};
