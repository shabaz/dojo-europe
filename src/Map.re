/* This is the basic component. */

type state = {people: option(array(Fetcher.data))};

type action =
  | SetData(array(Fetcher.data));

let component = ReasonReact.reducerComponent("Map");

let make = _children => {
  ...component,
  didMount: self => {
    Fetcher.fetchPost(
      ~url="https://immense-river-25513.herokuapp.com/add-location",
      ~body="shabaz",
    );
    Fetcher.fetchGet(
      ~url="https://immense-river-25513.herokuapp.com/locations", ~cb=data => {
      Js.log(Belt.Array.map(data, Fetcher.username));
      self.send(SetData(data));
    });
  },
  initialState: () => {people: None},
  reducer: (action, state) =>
    switch (action) {
    | SetData(people) => ReasonReact.Update({people: Some(people)})
    },
  render: self =>
    <div>
      <ComposableMap>
        <ZoomableGroup>
          <Geographies geography="world-50m.json">
            ...(
                 (geographies, projection) =>
                   geographies
                   |. Belt.Array.mapWithIndex((i, geography) =>
                        <Geography
                          key=(string_of_int(i))
                          geography
                          projection
                        />
                      )
                   |. ReasonReact.array
               )
          </Geographies>
          (
            switch (self.state.people) {
            | None => ReasonReact.null
            | Some(people) =>
              <Markers>
                (
                  people
                  |. Belt.Array.map(person =>
                       person
                       |. Fetcher.location
                       |. (
                         loc =>
                           <Marker marker={coordinates: loc}>
                             <circle cx="0" cy="0" r="2" fill="red" />
                           </Marker>
                       )
                     )
                  |. ReasonReact.array
                )
              </Markers>
            }
          )
        </ZoomableGroup>
      </ComposableMap>
      <div>
        (
          switch (self.state.people) {
          | None => ReasonReact.string("no people")
          | Some(people) =>
            people
            |. Belt.Array.map(person =>
                 person |. Fetcher.username |. ReasonReact.string
               )
            |. ReasonReact.array
          }
        )
      </div>
    </div>,
};