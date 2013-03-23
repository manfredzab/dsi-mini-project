################################################################################
# Automatically-generated file. Do not edit!
################################################################################

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
./src/abstract_join_iterator.o \
./src/abstract_multiway_sort_merge_join_trie_iterator.o \
./src/argument_parser.o \
./src/binary_search_tree.o \
./src/binary_search_tree_trie_iterator.o \
./src/binary_sort_merge_join.o \
./src/binary_sort_merge_join_iterator.o \
./src/cascading_sort_merge_join.o \
./src/data_parser.o \
./src/leapfrog_join_iterator.o \
./src/leapfrog_join_trie_iterator.o \
./src/linear_iterator.o \
./src/main.o \
./src/multiway_sort_merge_join_iterator.o \
./src/multiway_sort_merge_join_trie_iterator.o \
./src/printer.o \
./src/simple_iterator.o \
./src/trie.o \
./src/trie_trie_iterator.o 

CC_DEPS += \
./src/abstract_join_iterator.d \
./src/abstract_multiway_sort_merge_join_trie_iterator.d \
./src/argument_parser.d \
./src/binary_search_tree.d \
./src/binary_search_tree_trie_iterator.d \
./src/binary_sort_merge_join.d \
./src/binary_sort_merge_join_iterator.d \
./src/cascading_sort_merge_join.d \
./src/data_parser.d \
./src/leapfrog_join_iterator.d \
./src/leapfrog_join_trie_iterator.d \
./src/linear_iterator.d \
./src/main.d \
./src/multiway_sort_merge_join_iterator.d \
./src/multiway_sort_merge_join_trie_iterator.d \
./src/printer.d \
./src/simple_iterator.d \
./src/trie.d \
./src/trie_trie_iterator.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


