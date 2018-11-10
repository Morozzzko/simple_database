open Utils;
open Utils.Operators;

type node('key, 'value) = {
  key: 'key,
  value: 'value,
  left: option(node('key, 'value)),
  right: option(node('key, 'value)),
};

type t('key, 'value) = node('key, 'value);

let make = (key, value) => {key, value, left: None, right: None};

let rec insert = (key, value, tree) => {
  let newNode =
    Option.mapDefaultDelayed(insert(key, value), () => make(key, value));
  if (key < tree.key) {
    {...tree, left: newNode(tree.left) |> Option.return};
  } else if (key > tree.key) {
    {...tree, right: newNode(tree.right) |> Option.return};
  } else {
    tree;
  };
};

let rec search = (searchKey, {key as currentKey, left, right, value}) =>
  switch (searchKey <=> currentKey, left, right) {
  | (`Equal, _, _) => Some(value)
  | (`LessThan, Some(left), _) => search(searchKey, left)
  | (`GreaterThan, _, Some(right)) => search(searchKey, right)
  | _ => None
  };
