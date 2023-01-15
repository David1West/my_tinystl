#ifndef  MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

namespace mstl{

	template<typename T>
	inline T* _allocate(ptrdiff_t size,T *) {
		std::set_new_handler(0);
		T* temp= (T*)::operator new((size_t)(size * sizeof(T)));
		if (temp == 0) {
			std::cerr<<"out of memory" << std::endl;
			exit(1);
		}
		return temp;
	}

	template<typename T>
	inline void _deallocate(T * buffer) {
		::operator delete(buffer);
	}

	template<typename T>
	struct allocator {
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<typename U>
		struct rebind {
			typedef typename allocator<U> other;
		};

		allocator() = default;
		allocator(const allocator&) = default;

		template<typename U>
		allocator(const allcator<U>& rhs)=default;

		~allocator() = default;


		pointer allocate(size_type n,const void* hint = 0) {
			return _allocate((difference_type)(n),(pointer)(0));
		}



		void deallocate(pointer p, size_type t) {
			_deallocate(p);
		}

		pointer allocator::address(reference x) const {
			return static_cast<pointer>( & x);
		}
		const_pointer allocator::address(const_reference x) const {
			return static_cast<const_pointer>(&x)
		}

		size_type max_size() const {
			return std::UINT32_MAX / sizeof(T);
		}

		void destroy(pointer p) {
			mstl::destroy(p);
		}

		void construct(pointer p, const T& value) {
			mstl::construct(p,value);//调用util.h里的construct
		}

		void construct(pointer p, T&& value) {
			mstl::construct(mstl::move(value));
		}

		template<typename ...Args>
		void construct(pointer p,Args && ... args) {
			mstl::construct(forward<Args>(args...));
		}

		template<typename ForwardIter>
		void deallocate(ForwardIter first,Forward last) {
			mstl::destroy(first,last);
		}

	};

	class allocator<void> {

	};
}


#endif // ! MY_ALLOCATOR_H
