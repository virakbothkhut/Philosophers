# Philosophers

Ket understanding of following concepts:
- Threads: Each philo is seperate thread, allowing simultanous actions like **thinking**, **eating** and **sleeping.**
- Mutexes: Prevent multi threads accessing shared resourses(forks), thus avoiding race condition.
- Deadlocks: Action that philos holds 1 folk and waits for the other
- Starvation: Ensure very philo get a chance to eat and nonne are left waiting indefinitely.

// valgrind
// --fair-sched=yes
// --trace-children=yes
// --tool=memcheck
// --leak-check=full
// --tool=helgrind
// --tool=drd
// --read-var-info=yes
// --show-reachable=yes


 -fsanitize=thread. put it on makefile 
setarch $(uname -m) -R $SHELL
