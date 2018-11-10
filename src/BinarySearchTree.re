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
  let newNode = Option.mapDefault(insert(key, value), make(key, value));
  if (key < tree.key) {
    {...tree, left: Some(newNode(tree.left))};
  } else if (key > tree.key) {
    {...tree, right: Some(newNode(tree.right))};
  } else {
    tree;
  };
};

let rec search = (searchKey, {key, left, right, value}) =>
  switch (searchKey <=> key, left, right) {
  | (`Equal, _, _) => Some(value)
  | (`LessThan, Some(left), _) => search(searchKey, left)
  | (`GreaterThan, _, Some(right)) => search(searchKey, right)
  | _ => None
  };

let _deleteNode = ({left, right} as tree) =>
  switch (left, right) {
  | (None, None) => None
  | (Some(left), None) => Some(left)
  | (None, Some(right)) => Some(right)
  | (Some(left), Some(right)) =>
    switch (right.left) {
    | None => Some({...right, left: Some(left)})
    | Some(_) => Some(tree)
    }
  };

let rec delete = (key, tree) =>
  switch (key <=> tree.key) {
  | `LessThan => Some({...tree, left: Option.(tree.left >>= delete(key))})
  | `GreaterThan =>
    Some({...tree, right: Option.(tree.right >>= delete(key))})
  | `Equal => _deleteNode(tree)
  };
