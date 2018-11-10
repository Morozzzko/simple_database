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
