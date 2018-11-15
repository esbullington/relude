open Jest;
open Expect;

module Array = Relude_Array;
module Int = Relude_Int;

describe("Array", () => {
  test("length empty array", () =>
    expect(Array.length([||])) |> toEqual(0)
  );

  test("length non-empty array", () =>
    expect(Array.length([|1, 2, 3|])) |> toEqual(3)
  );

  test("isEmpty is true for empty array", () =>
    expect(Array.isEmpty([||])) |> toBe(true)
  );

  test("isEmpty is false for non-empty array", () =>
    expect(Array.isEmpty([|1|])) |> toBe(false)
  );

  test("isNotEmpty is false for empty array", () =>
    expect(Array.isNotEmpty([||])) |> toBe(false)
  );

  test("isNotEmpty is true for non-empty array", () =>
    expect(Array.isNotEmpty([|1|])) |> toBe(true)
  );

  test("empty is []", () =>
    expect(Array.empty) |> toEqual([||])
  );

  test("pure creates a one-item array", () =>
    expect(Array.pure(123)) |> toEqual([|123|])
  );

  test("repeat creates a array of n items", () =>
    expect(Array.repeat(3, "a")) |> toEqual([|"a", "a", "a"|])
  );

  test("makeWithIndex creates a array of n items using f", () =>
    expect(Array.makeWithIndex(3, i => i + 2)) |> toEqual([|2, 3, 4|])
  );

  test("concat", () =>
    expect(Array.concat([|1, 2|], [|3, 4|])) |> toEqual([|1, 2, 3, 4|])
  );

  test("cons", () =>
    expect(Array.cons(1, [|2, 3|])) |> toEqual([|1, 2, 3|])
  );

  test("uncons empty array", () =>
    expect(Array.uncons([||])) |> toEqual(None)
  );

  test("uncons single item array", () =>
    expect(Array.uncons([|1|])) |> toEqual(Some((1, [||])))
  );

  test("uncons multi item array", () =>
    expect(Array.uncons([|1, 2, 3|])) |> toEqual(Some((1, [|2, 3|])))
  );

  test("prepend", () =>
    expect(Array.prepend(1, [|2, 3|])) |> toEqual([|1, 2, 3|])
  );

  test("append", () =>
    expect(Array.append(1, [|2, 3|])) |> toEqual([|2, 3, 1|])
  );

  test("foldLeft", () =>
    expect(
      Array.foldLeft(
        (acc, curr) => Array.append(curr, acc),
        [||],
        [|1, 2, 3, 4, 5|],
      ),
    )
    |> toEqual([|1, 2, 3, 4, 5|])
  );

  test("foldRight", () =>
    expect(
      Array.foldRight(
        (curr, acc) => Array.append(curr, acc),
        [||],
        [|1, 2, 3, 4, 5|],
      ),
    )
    |> toEqual([|5, 4, 3, 2, 1|])
  );

  test("scanLeft", () =>
    expect(
      Array.scanLeft(
        (acc, curr) => Array.append(curr, acc),
        [||],
        [|1, 2, 3, 4, 5|],
      ),
    )
    |> toEqual([|
         [|1|],
         [|1, 2|],
         [|1, 2, 3|],
         [|1, 2, 3, 4|],
         [|1, 2, 3, 4, 5|],
       |])
  );

  test("scanRight", () =>
    expect(
      Array.scanRight(
        (curr, acc) => Array.append(curr, acc),
        [||],
        [|1, 2, 3, 4, 5|],
      ),
    )
    |> toEqual([|
         [|5, 4, 3, 2, 1|],
         [|5, 4, 3, 2|],
         [|5, 4, 3|],
         [|5, 4|],
         [|5|],
       |])
  );

  test("get empty array", () =>
    expect(0[[||]]) |> toEqual(None)
  );

  test("get success", () =>
    expect(2[[|0, 10, 20, 30|]]) |> toEqual(Some(20))
  );

  test("get failure", () =>
    expect(10[[|0, 10, 20, 30|]]) |> toEqual(None)
  );

  test("head empty array", () =>
    expect(Array.head([||])) |> toEqual(None)
  );

  test("head single item array", () =>
    expect(Array.head([|1|])) |> toEqual(Some(1))
  );

  test("head multi-item array", () =>
    expect(Array.head([|1, 2, 3|])) |> toEqual(Some(1))
  );

  test("tail empty array", () =>
    expect(Array.tail([||])) |> toEqual(None)
  );

  test("tail single item array", () =>
    expect(Array.tail([|1|])) |> toEqual(Some([||]))
  );

  test("tail multi-item array", () =>
    expect(Array.tail([|1, 2, 3|])) |> toEqual(Some([|2, 3|]))
  );

  test("tailOrEmpty empty array", () =>
    expect(Array.tailOrEmpty([||])) |> toEqual([||])
  );

  test("tailOrEmpty single item array", () =>
    expect(Array.tailOrEmpty([|1|])) |> toEqual([||])
  );

  test("tailOrEmpty multi-item array", () =>
    expect(Array.tailOrEmpty([|1, 2, 3|])) |> toEqual([|2, 3|])
  );

  test("init empty array", () =>
    expect(Array.init([||])) |> toEqual(None)
  );

  test("init single item array", () =>
    expect(Array.init([|1|])) |> toEqual(Some([||]))
  );

  test("init multi item array", () =>
    expect(Array.init([|1, 2, 3, 4|])) |> toEqual(Some([|1, 2, 3|]))
  );

  test("last empty array", () =>
    expect(Array.last([||])) |> toEqual(None)
  );

  test("last single item array", () =>
    expect(Array.last([|1|])) |> toEqual(Some(1))
  );

  test("last multi item array", () =>
    expect(Array.last([|1, 2, 3, 4|])) |> toEqual(Some(4))
  );

  test("take zero from empty array", () =>
    expect(Array.take(0, [||])) |> toEqual(Some([||]))
  );

  test("take non-zero from empty array", () =>
    expect(Array.take(2, [||])) |> toEqual(None)
  );

  test("take non-zero from short array", () =>
    expect(Array.take(2, [|1|])) |> toEqual(None)
  );

  test("take non-zero from equal array", () =>
    expect(Array.take(2, [|1, 2|])) |> toEqual(Some([|1, 2|]))
  );

  test("take non-zero from long array", () =>
    expect(Array.take(2, [|1, 2, 3|])) |> toEqual(Some([|1, 2|]))
  );

  test("takeUpTo zero from empty array", () =>
    expect(Array.takeUpTo(0, [||])) |> toEqual([||])
  );

  test("takeUpTo non-zero from empty array", () =>
    expect(Array.takeUpTo(2, [||])) |> toEqual([||])
  );

  test("takeUpTo non-zero from short array", () =>
    expect(Array.takeUpTo(2, [|1|])) |> toEqual([|1|])
  );

  test("takeUpTo non-zero from equal array", () =>
    expect(Array.takeUpTo(2, [|1, 2|])) |> toEqual([|1, 2|])
  );

  test("takeUpTo non-zero from long array", () =>
    expect(Array.takeUpTo(2, [|1, 2, 3|])) |> toEqual([|1, 2|])
  );

  test("takeWhile empty array", () =>
    expect(Array.takeWhile(a => a < 2, [||])) |> toEqual([||])
  );

  test("takeWhile array", () =>
    expect(Array.takeWhile(a => a < 2, [|0, 1, 2, 3|]))
    |> toEqual([|0, 1|])
  );

  test("takeWhile array condition never true", () =>
    expect(Array.takeWhile(a => a < 0, [|0, 1, 2, 3|])) |> toEqual([||])
  );

  test("takeWhile array condition never false", () =>
    expect(Array.takeWhile(a => a < 10, [|0, 1, 2, 3|]))
    |> toEqual([|0, 1, 2, 3|])
  );

  test("drop zero from empty array", () =>
    expect(Array.drop(0, [||])) |> toEqual(Some([||]))
  );

  test("drop some from short array ", () =>
    expect(Array.drop(1, [|1, 2|])) |> toEqual(Some([|2|]))
  );

  test("drop some from equal array ", () =>
    expect(Array.drop(2, [|1, 2|])) |> toEqual(Some([||]))
  );

  test("drop some from long array ", () =>
    expect(Array.drop(2, [|1, 2, 3, 4|])) |> toEqual(Some([|3, 4|]))
  );

  test("drop more from long array ", () =>
    expect(Array.drop(5, [|1, 2, 3, 4|])) |> toEqual(None)
  );

  test("dropUpTo zero from empty array", () =>
    expect(Array.dropUpTo(0, [||])) |> toEqual([||])
  );

  test("dropUpTo some from short array ", () =>
    expect(Array.dropUpTo(1, [|1, 2|])) |> toEqual([|2|])
  );

  test("dropUpTo some from equal array ", () =>
    expect(Array.dropUpTo(2, [|1, 2|])) |> toEqual([||])
  );

  test("dropUpTo some from long array ", () =>
    expect(Array.dropUpTo(2, [|1, 2, 3, 4|])) |> toEqual([|3, 4|])
  );

  test("dropUpTo more from long array ", () =>
    expect(Array.dropUpTo(5, [|1, 2, 3, 4|])) |> toEqual([||])
  );

  test("dropWhile empty array", () =>
    expect(Array.dropWhile(a => a < 2, [||])) |> toEqual([||])
  );

  test("dropWhile array", () =>
    expect(Array.dropWhile(a => a < 2, [|0, 1, 2, 1, 3|]))
    |> toEqual([|2, 1, 3|])
  );

  test("dropWhile array condition never true", () =>
    expect(Array.dropWhile(a => a < 0, [|0, 1, 2, 3|]))
    |> toEqual([|0, 1, 2, 3|])
  );

  test("dropWhile array condition never false", () =>
    expect(Array.dropWhile(a => a < 10, [|0, 1, 2, 3|])) |> toEqual([||])
  );

  test("filter", () =>
    expect(
      Array.filter(
        i => i mod 2 == 0,
        [|1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 10|],
      ),
    )
    |> toEqual([|2, 4, 6, 8, 10, 10|])
  );

  test("filterWithIndex", () =>
    expect(
      Array.filterWithIndex(
        (v, i) => i mod 2 == 0 || v == 3,
        [|1, 3, 3, 4, 5, 6|],
      ),
    )
    |> toEqual([|1, 3, 3, 5|])
  );

  test("find not found", () =>
    expect(Array.find(a => a == 3, [|0, 1, 2|])) |> toEqual(None)
  );

  test("find found", () =>
    expect(Array.find(a => a == 2, [|0, 1, 2, 3, 4|])) |> toEqual(Some(2))
  );

  test("findWithIndex", () =>
    expect(Array.findWithIndex((a, i) => a == 3 || i == 2, [|0, 1, 2, 3|]))
    |> toEqual(Some(2))
  );

  test("partition", () =>
    expect(Array.partition(a => a mod 2 == 0, [|0, 1, 2, 3, 4, 5|]))
    |> toEqual(([|0, 2, 4|], [|1, 3, 5|]))
  );

  test("splitAt", () =>
    expect(Array.splitAt(3, [|0, 1, 2, 3, 4, 5|]))
    |> toEqual(Some(([|0, 1, 2|], [|3, 4, 5|])))
  );

  test("prependToAll", () =>
    expect(Array.prependToAll(0, [|0, 1, 2|]))
    |> toEqual([|0, 0, 0, 1, 0, 2|])
  );

  test("intersperse", () =>
    expect(Array.intersperse(",", [|"a", "b", "c"|]))
    |> toEqual([|"a", ",", "b", ",", "c"|])
  );

  test("replicate", () =>
    expect(Array.replicate(3, [|"a", "b", "c"|]))
    |> toEqual([|"a", "b", "c", "a", "b", "c", "a", "b", "c"|])
  );

  test("zip same length array", () =>
    expect(Array.zip([|1, 2, 3|], [|"4", "5", "6"|]))
    |> toEqual([|(1, "4"), (2, "5"), (3, "6")|])
  );

  test("zip different length array", () =>
    expect(Array.zip([|1, 2, 3|], [|"4", "5"|]))
    |> toEqual([|(1, "4"), (2, "5")|])
  );

  test("zipWith", () =>
    expect(Array.zipWith((a, b) => a + b, [|1, 2, 3|], [|4, 5, 6|]))
    |> toEqual([|5, 7, 9|])
  );

  test("zipWithIndex", () =>
    expect(Array.zipWithIndex([|"a", "b", "c"|]))
    |> toEqual([|("a", 0), ("b", 1), ("c", 2)|])
  );

  test("unzip", () =>
    expect(Array.unzip([|(1, 2), (3, 4), (5, 6)|]))
    |> toEqual(([|1, 3, 5|], [|2, 4, 6|]))
  );

  test("sortWithInt", () =>
    expect(Array.sortWithInt(Int.compareAsInt, [|2, 0, 1, 3, 5, (-1)|]))
    |> toEqual([|(-1), 0, 1, 2, 3, 5|])
  );

  test("sort", () =>
    expect(Array.sort(Int.compare, [|2, 0, 1, 3, 5, (-1)|]))
    |> toEqual([|(-1), 0, 1, 2, 3, 5|])
  );

  test("reverse", () =>
    expect(Array.reverse([|1, 2, 3, 4, 5|])) |> toEqual([|5, 4, 3, 2, 1|])
  );

  test("contains false", () =>
    expect(Array.contains(Int.eq, 10, [|0, 1, 2, 3, 4|])) |> toEqual(false)
  );

  test("indexOf success", () =>
    expect(Array.indexOf(Int.eq, 30, [|0, 10, 20, 30, 40|])) |> toEqual(Some(3))
  );

  test("indexOf failure", () =>
    expect(Array.indexOf(Int.eq, 500, [|0, 10, 20, 30, 40|])) |> toEqual(None)
  );

  test("contains true", () =>
    expect(Array.contains(Int.eq, 3, [|0, 1, 2, 3, 4|])) |> toEqual(true)
  );

  test("any empty", () =>
    expect(Array.any(a => a > 2, [||])) |> toEqual(false)
  );

  test("any true", () =>
    expect(Array.any(a => a > 2, [|0, 1, 2, 3|])) |> toEqual(true)
  );

  test("any false", () =>
    expect(Array.any(a => a > 10, [|0, 1, 2, 3|])) |> toEqual(false)
  );

  test("all empty", () =>
    expect(Array.all(a => a > 2, [||])) |> toEqual(true)
  );

  test("all true", () =>
    expect(Array.all(a => a > (-1), [|0, 1, 2, 3|])) |> toEqual(true)
  );

  test("all false", () =>
    expect(Array.all(a => a < 3, [|0, 1, 2, 3|])) |> toEqual(false)
  );

  test("distinct", () =>
    expect(Array.distinct(Int.eq, [|6, 1, 1, 2, 1, 3, 2, 3, 2, 4, 5, 5|]))
    |> toEqual([|6, 1, 2, 3, 4, 5|])
  );

  test("map", () =>
    expect(Array.map(a => a + 2, [|1, 2, 3|])) |> toEqual([|3, 4, 5|])
  );

  test("apply", () =>
    expect(Array.apply([|a => a + 2, a => a * 3|], [|1, 2, 3|]))
    |> toEqual([|3, 4, 5, 3, 6, 9|])
  );

  test("flatMap", () =>
    expect(Array.flatMap([|1, 2, 3|], a => [|a, a|]))
    |> toEqual([|1, 1, 2, 2, 3, 3|])
  );

  test("flatten", () =>
    expect(Array.flatten([|[|1, 2, 3|], [|4, 5|]|]))
    |> toEqual([|1, 2, 3, 4, 5|])
  );

  test("fromList", () =>
    expect(Array.fromList([1, 2, 3])) |> toEqual([|1, 2, 3|])
  );

  test("toList", () =>
    expect(Array.toList([|1, 2, 3|])) |> toEqual([1, 2, 3])
  );

  test("eq returns true if array items are equal", () =>
    expect(Array.eq(Int.eq, [|1, 2, 3|], [|1, 2, 3|])) |> toBe(true)
  );

  test("eq returns false if array items are not equal", () =>
    expect(Array.eq(Int.eq, [|1, 2, 3|], [|1, 2, 4|])) |> toBe(false)
  );

  test("eq returns false if array are of different sizes", () =>
    expect(Array.eq(Int.eq, [|1|], [|1, 2|])) |> toBe(false)
  );

  test("eqM returns true if array items are equal", () =>
    expect(Array.eqM((module Int.Eq), [|1, 2, 3|], [|1, 2, 3|]))
    |> toBe(true)
  );

  test("eqM returns false if array items are not equal", () =>
    expect(Array.eqM((module Int.Eq), [|1, 2, 3|], [|1, 2, 4|]))
    |> toBe(false)
  );

  test("mkString", () =>
    expect(Array.mkString(", ", [|"a", "b", "c"|])) |> toEqual("a, b, c")
  );

  test("show", () =>
    expect(Array.show(string_of_int, [|1, 2, 3|])) |> toEqual("[1, 2, 3]")
  );
  /*
   test("void", () =>
     expect(Array.void([1, 2, 3])) |> toEqual([(), (), ()])
   );

   test("flap", () =>
     expect(Array.flap([a => a + 1, a => a + 2, a => a + 3], 5))
     |> toEqual([6, 7, 8])
   );

   test("map2", () =>
     expect(Array.map2((a, b) => a + b, [1, 2], [3, 4]))
     |> toEqual([4, 5, 5, 6])
   );

   test("map3", () =>
     expect(Array.map3((a, b, c) => a + b + c, [1, 2], [3, 4], [10, 20]))
     |> toEqual([14, 24, 15, 25, 15, 25, 16, 26])
   );

   test("map4", () =>
     expect(
       Array.map4(
         (a, b, c, d) => a + b + c + d,
         [1, 2],
         [3, 4],
         [10, 20],
         [100, 200],
       ),
     )
     |> toEqual([
          114,
          214,
          124,
          224,
          115,
          215,
          125,
          225,
          115,
          215,
          125,
          225,
          116,
          216,
          126,
          226,
        ])
   );
   */
});
