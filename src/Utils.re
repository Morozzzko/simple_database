/*
 For some reason I couldn't get it to work properly
 Courtesy of https://github.com/planado/reason-commons
 especially Vadim Safonov (imamatory) and Nikita Shilnikov (flash-gordon)
  */
module Option = {
  type t('a) = option('a);
  let mapDefault = (f: 'a => 'b, l: 'b, v: t('a)) =>
    switch (v) {
    | None => l
    | Some(v) => f(v)
    };

  let isSome = v =>
    switch (v) {
    | Some(v) => true
    | None => false
    };

  module Functor = {
    let map = (f: 'a => 'b, v: t('a)): t('b) =>
      switch (v) {
      | None => None
      | Some(x) => Some(f(x))
      };
  };

  include Functor;

  module Monad = {
    let return = input => Some(input);
    let bind = (v: t('a), f: 'a => t('b)): t('b) =>
      switch (v) {
      | Some(x) => f(x)
      | None => None
      };
    let (>>=) = bind;
  };

  include Monad;
};

module Operators = {
  let (<=>) = (a, b) =>
    if (a == b) {
      `Equal;
    } else if (a < b) {
      `LessThan;
    } else {
      `GreaterThan;
    };
};
