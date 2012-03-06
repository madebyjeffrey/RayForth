// As defined here: http://preney.ca/paul/2012/02/06/applying-tuple-to-functors-and-functions-the-home-stretch-part-ii/
#ifndef APPLY_TUPLE
#define APPLY_TUPLE

#include <cstddef>
#include <tuple>
//#include <functional>
#include <type_traits>
/*
template <std::size_t...>
struct indices;

template <std::size_t Begin, std::size_t End, typename Indices>
struct make_seq_indices_impl;

template <std::size_t Begin, std::size_t End, std::size_t... Indices>
struct make_seq_indices_impl<Begin, End, indices<Indices...>>
{
  using type =
	typename
	  make_seq_indices_impl<Begin+1, End,indices<Indices..., Begin>
	>::type
  ;
};

template <std::size_t End, std::size_t... Indices>
struct make_seq_indices_impl<End, End, indices<Indices...>>
{
  using type = indices<Indices...>;
};

template <std::size_t Begin, std::size_t End>
using make_seq_indices =
  typename make_seq_indices_impl<Begin, End, indices<>>::type;
  
template <typename F>
using return_type = typename std::result_of<F>::type;

template <typename Tuple>
constexpr std::size_t tuple_size()
{
  return std::tuple_size<typename std::decay<Tuple>::type>::value;
}

template <
  typename Op,
  typename T,
  template <std::size_t...> class I,
  std::size_t... Indices
>
constexpr auto apply_tuple_return_type_impl(
  Op&& op, T&& t, I<Indices...>
)
  -> return_type<
	Op(decltype(std::get<Indices>(std::forward<T>(t)))...)
  >;

template <typename Op, typename T>
constexpr auto apply_tuple_return_type(Op&& op, T&& t)
  -> decltype(
	apply_tuple_return_type_impl(
	  op, t, make_seq_indices<0,tuple_size<T>()>{}
	)
  );
  
template <typename T>
constexpr bool is_void()
{
  return std::is_void<T>::value;
}

template <typename F>
constexpr bool returns_void()
{
  return std::is_void<return_type<F>>::value;
}

template <bool Cond, typename T>
using enable_if = typename std::enable_if<Cond,T>::type;

template <typename Ret>
using if_returns_void_case = enable_if<is_void<Ret>(),Ret>;

template <typename Ret>
using if_returns_nonvoid_case = enable_if<!is_void<Ret>(),Ret>;

template <typename Op, typename... Args>
inline auto apply(Op&& op, Args&&... args)
  -> if_returns_nonvoid_case<return_type<Op(Args...)>>
{
  return op( std::forward<Args>(args)... );
}

template <typename Op, typename... Args>
inline auto apply(Op&& op, Args&&... args)
  -> if_returns_void_case<return_type<Op(Args...)>>
{
  op( std::forward<Args>(args)... );
}

// void cannot be the default value for Enable...
template <typename Indices, typename Ret, typename Enable = Ret>
struct apply_tuple_impl;

// void return case...
template <
  template <std::size_t...> class I, std::size_t... Indices,
  typename Ret
>
struct apply_tuple_impl<I<Indices...>, Ret, void>
{
  template <typename Op, typename T>
  inline static Ret apply_tuple(Op&& op, T&& t)
  {
	op(
	  std::forward<
		decltype(std::get<Indices>(std::forward<T>(t)))
	  >(std::get<Indices>(std::forward<T>(t)))...
	);
  }
};

// non-void return case...
template <
  template <std::size_t...> class I, std::size_t... Indices,
  typename Ret
>
struct apply_tuple_impl<
  I<Indices...>,
  Ret,
  if_returns_nonvoid_case<Ret>
>
{
  template <typename Op, typename T>
  inline static Ret apply_tuple(Op&& op, T&& t)
  {
	return op(
	  std::forward<
		decltype(std::get<Indices>(std::forward<T>(t)))
	  >(std::get<Indices>(std::forward<T>(t)))...
	);
  }
};

// non-void return case...
template <typename Op, typename Tuple>
inline auto apply_tuple(Op&& op, Tuple&& t) ->
  if_returns_nonvoid_case<
	decltype(
	  apply_tuple_return_type(
		std::forward<Op>(op), std::forward<Tuple>(t)
	  )
	)
  >
{
  return
	apply_tuple_impl<
	  make_seq_indices<0,tuple_size<Tuple>()>,
	  decltype(
		apply_tuple_return_type(
		  std::forward<Op>(op), std::forward<Tuple>(t)
		)
	  )
	>::apply_tuple(std::forward<Op>(op),std::forward<Tuple>(t))
  ;
}

// void return case...
template <typename Op, typename Tuple>
inline auto apply_tuple(Op&& op, Tuple&& t) ->
  if_returns_void_case<
	decltype(
	  apply_tuple_return_type(
		std::forward<Op>(op), std::forward<Tuple>(t)
	  )
	)
  >
{
  apply_tuple_impl<
	make_seq_indices<0,tuple_size<Tuple>()>,
	decltype(
	  apply_tuple_return_type(
		std::forward<Op>(op), std::forward<Tuple>(t)
	  )
	)
  >::apply_tuple(std::forward<Op>(op),std::forward<Tuple>(t));
}
*/

#endif