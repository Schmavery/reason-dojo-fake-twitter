open ReasonUrql;

/* let client = Client.make(~url="http://localhost:9999/graphql", ()); */
let client = Client.make(~url="http://cc265406.ngrok.io/graphql", ());
/* let client = Client.make(~url="http://10.111.4.23:9999/graphql", ()); */

ReactDOMRe.renderToElementWithId(
  <Provider value=client> <Feed /> </Provider>,
  "root",
);
