let client = Client.make(~url="https://localhost:3000/graphql", ());

ReactDOMRe.renderToElementWithId(
  <Provider client> <Greeting name="John" /> </Provider>,
  "root",
);
