# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/abstract_join_iterator.cc \
../src/abstract_multiway_sort_merge_join_trie_iterator.cc \
../src/argument_parser.cc \
../src/binary_search_tree.cc \
../src/binary_search_tree_trie_iterator.cc \
../src/binary_sort_merge_join.cc \
../src/binary_sort_merge_join_iterator.cc \
../src/cascading_sort_merge_join.cc \
../src/data_parser.cc \
../src/leapfrog_join_iterator.cc \
../src/leapfrog_join_trie_iterator.cc \
../src/linear_iterator.cc \
../src/main.cc \
../src/multiway_sort_merge_join_iterator.cc \
../src/multiway_sort_merge_join_trie_iterator.cc \
../src/printer.cc \
../src/simple_iterator.cc \
../src/trie.cc \
../src/trie_trie_iterator.cc 

OBJS += \
./obj/abstract_join_iterator.o \
./obj/abstract_multiway_sort_merge_join_trie_iterator.o \
./obj/argument_parser.o \
./obj/binary_search_tree.o \
./obj/binary_search_tree_trie_iterator.o \
./obj/binary_sort_merge_join.o \
./obj/binary_sort_merge_join_iterator.o \
./obj/cascading_sort_merge_join.o \
./obj/data_parser.o \
./obj/leapfrog_join_iterator.o \
./obj/leapfrog_join_trie_iterator.o \
./obj/linear_iterator.o \
./obj/main.o \
./obj/multiway_sort_merge_join_iterator.o \
./obj/multiway_sort_merge_join_trie_iterator.o \
./obj/printer.o \
./obj/simple_iterator.o \
./obj/trie.o \
./obj/trie_trie_iterator.o 

CC_DEPS += \
./obj/abstract_join_iterator.d \
./obj/abstract_multiway_sort_merge_join_trie_iterator.d \
./obj/argument_parser.d \
./obj/binary_search_tree.d \
./obj/binary_search_tree_trie_iterator.d \
./obj/binary_sort_merge_join.d \
./obj/binary_sort_merge_join_iterator.d \
./obj/cascading_sort_merge_join.d \
./obj/data_parser.d \
./obj/leapfrog_join_iterator.d \
./obj/leapfrog_join_trie_iterator.d \
./obj/linear_iterator.d \
./obj/main.d \
./obj/multiway_sort_merge_join_iterator.d \
./obj/multiway_sort_merge_join_trie_iterator.d \
./obj/printer.d \
./obj/simple_iterator.d \
./obj/trie.d \
./obj/trie_trie_iterator.d 


# Each subdirectory must supply rules for building sources it contributes
obj/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


