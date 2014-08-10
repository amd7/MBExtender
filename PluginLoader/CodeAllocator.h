#pragma once

#include <cstdint>
#include <stack>

namespace CodeInjection
{
	/// <summary>
	/// Simple mechanism for allocating blocks of executable code which can be written to and read from.
	/// </summary>
	class CodeAllocator
	{
	public:
		CodeAllocator();
		~CodeAllocator();

		/// <summary>
		/// Allocates a block of code.
		/// </summary>
		/// <param name="size">The size of the block to allocate.</param>
		/// <returns>The allocated block if successful, or <c>nullptr</c> on failure.</returns>
		void* allocate(size_t size);

	private:
		/// <summary>
		/// Ensures that a number of bytes is available in the buffer.
		/// If the buffer is too small, a new one will be allocated.
		/// </summary>
		/// <param name="size">The number of bytes requested.</param>
		/// <returns><c>true</c> on success.</returns>
		bool ensureAvailable(size_t size);

		/// <summary>
		/// Allocates a new buffer.
		/// </summary>
		/// <param name="minSize">The minimum size that the buffer should be.</param>
		/// <returns><c>true</c> on success.</returns>
		bool newBuffer(size_t minSize);

		/// <summary>
		/// Frees the memory occupied by a buffer.
		/// It must have been allocated with <see cref="newBuffer"/>.
		/// </summary>
		/// <param name="buffer">The buffer to release.</param>
		void releaseBuffer(void *buffer);

		/// <summary>
		/// Frees the memory occupied by all allocated buffers.
		/// </summary>
		void releaseAllBuffers();

		uint8_t *ptr;                 // Pointer to next free block of code
		size_t sizeRemaining;         // Number of bytes remaining in the current buffer
		std::stack<uint8_t*> buffers; // All buffers that have been allocated so far
	};
}