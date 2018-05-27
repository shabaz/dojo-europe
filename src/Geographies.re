[@bs.module "react-simple-maps"]
external geographiesClass : ReasonReact.reactClass = "Geographies";

let make =
    (~geography, children: (array(Types.geography), Types.projection) => 'a) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=geographiesClass,
    ~props={"geography": geography},
    children,
  );