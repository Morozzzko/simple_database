open Jest;

module BST = BinarySearchTree;

describe("insert", () => {
  open BST;
  open Expect;
  describe("insert values less than the root node key", () => {
    let originalTree = make(4, 0);
    let newTree = originalTree |> insert(2, 0);

    test("modifies the left branch", () =>
      expect(newTree.left)
      |> toEqual(Some({key: 2, value: 0, left: None, right: None}))
    );
    test("does not modify the right branch", () =>
      expect(newTree.right) |> toEqual(None)
    );
    test("does not modify the key", () =>
      expect(newTree.key) |> toEqual(4)
    );
    test("does not modify the value", () =>
      expect(newTree.value) |> toEqual(0)
    );
  });

  describe("insert values greater than the root node", () => {
    let originalTree = make(4, 0);
    let newTree = originalTree |> insert(6, 0);

    test("modifies the right branch", () =>
      expect(newTree.right)
      |> toEqual(Some({key: 6, value: 0, left: None, right: None}))
    );
    test("does not modify the left branch", () =>
      expect(newTree.left) |> toEqual(None)
    );
    test("does not modify the key", () =>
      expect(newTree.key) |> toEqual(4)
    );
    test("does not modify the value", () =>
      expect(newTree.value) |> toEqual(0)
    );
  });

  describe("insert values equal to the root node", () => {
    let originalTree = make(4, 0);
    let newTree = originalTree |> insert(4, 0);

    test("does not modify the left branch", () =>
      expect(newTree.left) |> toEqual(None)
    );
    test("does not modify the right branch", () =>
      expect(newTree.right) |> toEqual(None)
    );
    test("does not modify the key", () =>
      expect(newTree.key) |> toEqual(4)
    );
    test("does not modify the value", () =>
      expect(newTree.value) |> toEqual(0)
    );
  });

  describe("nested insert", () => {
    let tree = make(4, 0) |> insert(2, 0) |> insert(3, 0);

    test("moves value to the correct position", () =>
      expect(tree)
      |> toEqual({
           key: 4,
           value: 0,
           left:
             Some({
               key: 2,
               value: 0,
               left: None,
               right: Some({key: 3, value: 0, left: None, right: None}),
             }),
           right: None,
         })
    );
  });

  test("nested insert: two nodes", () => {
    let tree =
      make(4, "hello")
      |> insert(10, "world")
      |> insert(8, "left")
      |> insert(11, "right")
      |> insert(2, "ayy");
    expect(tree)
    |> toEqual({
         key: 4,
         value: "hello",
         left: Some({key: 2, value: "ayy", left: None, right: None}),
         right:
           Some({
             key: 10,
             value: "world",
             left: Some({key: 8, value: "left", left: None, right: None}),
             right: Some({key: 11, value: "right", left: None, right: None}),
           }),
       });
  });
});

describe("search", () => {
  open BST;
  open Expect;

  let tree =
    make(4, "hello")
    |> insert(2, "there")
    |> insert(5, "I am")
    |> insert(1, "confused");

  test("existing key", () =>
    expect(tree |> search(5)) |> toBe(Some("I am"))
  );
  test("non-existing key", () =>
    expect(tree |> search(124)) |> toBe(None)
  );
});

describe("remove", () => {
  open BST;
  open Expect;

  test("existing key: no children", () => {
    let tree = make(4, "hello") |> insert(2, "there") |> insert(6, "I am");
    expect(tree |> delete(6))
    |> toEqual(
         Some({
           key: 4,
           value: "hello",
           right: None,
           left: Some({key: 2, value: "there", left: None, right: None}),
         }),
       );
  });
  test("existing key: only left child", () => {
    let tree =
      make(4, "hello")
      |> insert(2, "there")
      |> insert(6, "I am")
      |> insert(5, "confused");
    expect(tree |> delete(6))
    |> toEqual(
         Some({
           key: 4,
           value: "hello",
           right: Some({key: 5, value: "confused", left: None, right: None}),
           left: Some({key: 2, value: "there", left: None, right: None}),
         }),
       );
  });
  test("existing key: only right child", () => {
    let tree =
      make(4, "hello")
      |> insert(2, "there")
      |> insert(6, "I am")
      |> insert(8, "there are too many keys!");
    expect(tree |> delete(6))
    |> toEqual(
         Some({
           key: 4,
           value: "hello",
           right:
             Some({
               key: 8,
               value: "there are too many keys!",
               left: None,
               right: None,
             }),
           left: Some({key: 2, value: "there", left: None, right: None}),
         }),
       );
  });
  describe("existing key: both children", () => {
    test("right subtree does not have left child", () => {
      let tree =
        make(4, "hello")
        |> insert(2, "there")
        |> insert(6, "I am")
        |> insert(5, "confused")
        |> insert(8, "there are too many keys!");
      expect(tree |> delete(6))
      |> toEqual(
           Some({
             key: 4,
             value: "hello",
             right:
               Some({
                 key: 8,
                 value: "there are too many keys!",
                 left:
                   Some({key: 5, value: "confused", left: None, right: None}),
                 right: None,
               }),
             left: Some({key: 2, value: "there", left: None, right: None}),
           }),
         );
    });
    test("right subtree has left child", () => {
      let tree =
        make(4, "hello")
        |> insert(2, "there")
        |> insert(6, "I am")
        |> insert(5, "confused")
        |> insert(8, "there are too many keys!")
        |> insert(7, "it's getting complicated");
      expect(tree |> delete(6))
      |> toEqual(
           Some({
             key: 4,
             value: "hello",
             right:
               Some({
                 key: 7,
                 value: "it's getting complicated",
                 left:
                   Some({key: 5, value: "confused", left: None, right: None}),

                 right:
                   Some({
                     key: 8,
                     value: "there are too many keys!",
                     left: None,
                     right: None,
                   }),
               }),
             left: Some({key: 2, value: "there", left: None, right: None}),
           }),
         );
    });
  });
  test("non-existing key", () => {
    let tree =
      make(4, "hello")
      |> insert(2, "there")
      |> insert(6, "I am")
      |> insert(5, "confused");

    expect(tree |> delete(10)) |> toEqual(Some(tree));
  });
});
