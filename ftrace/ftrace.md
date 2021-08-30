# Start Ftrace
Root of tracefs usually located at:
- /sys/kernel/debug/tracing/
- /sys/kernel/tracing/

dump trace:
```
#> cat trace (Read trace buffer)
#> echo > trace (Clean trace buffer)
or
#> cat trace_pipe (Reand and Clean trace buffer)
```
Or mount tracefs manually
- #> mount -t tracefs nodev /sys/kernel/tracing

# Function Tracer
ftrace stands for function tracer. It traces all kernel functions by leveraging compiler to insert a hook function(or callback like) to add tracepoint. 

Enable a tracer:
```
#> echo function > current_tracer
```

Stop tracer:
```
#> echo nop > current_tracer
```

Turn it off:
```
#> echo nop > current_tracer
```

Enable/Disable recording in the ring buffer:
```
#> echo 1 > tracing_on
#> echo 0 > tracing_on   (Note: still keeping tracing, overhead exists)
```

Trace Marker: Write string directly into ring buffer.
```
#> echo nop > current_tracer
#> echo 1 > tracing_on
#> echo 'hello world' > trace_marker
```
  - Pros: We can collaborate with trace buffer from userspace.
  - Cons: Waste buffer space
  
Trace filter:
```
#> echo foo > set_ftrace_notrace (not tracing, takes precedence over set_ftrace_filter)
#> echo bar wola > set_ftrace_filter (trace only)
#> echo > ster_ftrace_filter  (Clear)
```

Trace Graph: Friendly to show function caller & callee. But I don't use it so much. This is useful when you look into specific range of functions. I may choose printk instead.
```
#> echo function_graph > current_tracer
#> cat trace
```

# Trace Events
function tracer is still not enough. What about variable, parameters and other information we need to extract from kernel? Based on ftrace framework, we can customize what information to be recorded. There are already bunch of trace_events in linux kernel. For most useful trace_event to me is sched/irq events. Over 90% system performance issues can be narrowed down significantly by looking into sched/irq events.

Checking existed trace_events:
```
#> cat events
```

Enable Method1: events/$module/$sub_event/enable
```
#> echo nop > current_tracer
#> echo 1 > events/sched/sched_switch/enable
#> echo 1 > events/sched/sched_waking/enable
#> cat trace
```

Enable Method2: set_event
```
echo sched_switch sched_waking > set_event
```

Filter events: events/sched/sched_switch/filter
```
First, to check format of trace_event
#> cat events/sched/sched_switch/format
```

```
Second, follow the format showing as output from the above command and set filter value into parameters.
#> echo 'prev_comm == "bash" %% prev_state % 0x02' > events/sched/sched_switch/filter
#> echo 1 > events/sched/sched_switch/enable
#> echo > trace
#> cat trace
```

# General events setup 

```
# Clear tracers
echo nop > /sys/kernel/debug/tracing/current_tracer
# Clear events
echo > /sys/kernel/debug/tracing/set_event
echo sched_switch sched_wakeup sched_wakeup_new irq_handler_entry irq_handler_exit > /sys/kernel/debug/tracing/set_event

echo 0 > /sys/kernel/debug/tracing/tracing_on

# clean trace buffer
echo > /sys/kernel/debug/tracing/trace

# Start tracing
echo 1 > /sys/kernel/debug/tracing/tracing_on

# Stop tracing
echo 0 > /sys/kernel/debug/tracing/tracing_on

```

REF: https://embeddedbits.org/tracing-the-linux-kernel-with-ftrace/

