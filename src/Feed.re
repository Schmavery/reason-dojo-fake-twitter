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
  let ({ReasonUrql.Hooks.response}, _) = Hooks.useQuery(~request, ());

  <div>
    <hr />
    <div>
      {switch (response) {
       | Fetching => React.string("Load")
       | Error(e) =>
         switch (e.networkError) {
         | Some(exn) =>
           Js.log(exn);
           <div> {React.string("Network Error")} </div>;
         | None => <div> {React.string("No Network Error")} </div>
         }
       | NotFound => React.string("Not found")
       | Data(d) =>
         React.array(
           Array.map(post => <Tweet key={post##timestamp} post />, d##feed),
         )
       }}
    </div>
  </div>;
};
