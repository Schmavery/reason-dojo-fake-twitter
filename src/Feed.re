open ReasonUrql;

module GetFeed = [%graphql
  {|
  query feed {
    feed {
      message
      author
      timestamp
    }
  }
|}
];

module Tweet = {
  [@react.component]
  let make = (~post) =>
    <div> {React.string(post##author ++ ": " ++ post##message)} <br /> </div>;
};

[@react.component]
let make = () => {
  let request = GetFeed.make();
  let ({ReasonUrql.Hooks.response}, executeQuery) =
    Hooks.useQuery(~request, ());

  let refetch = React.useCallback(() => executeQuery(None));

  <div>
    <NewPost refetch />
    <hr />
    <div>
      {switch (response) {
       | Fetching => React.string("Load")
       | Error(e) =>
         switch (e.networkError) {
         | Some(exn) =>
           Js.log(exn);
           <div> "Network Error"->React.string </div>;
         | None => <div> "No Network Error"->React.string </div>
         }
       | NotFound => React.string("Not found???")
       | Data(d) =>
         React.array(
           Array.map(post => <Tweet key={post##timestamp} post />, d##feed),
         )
       }}
    </div>
  </div>;
};
