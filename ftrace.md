# Start Ftrace
Root of tracefs usually located at:
- /sys/kernel/debug/tracing/
- /sys/kernel/tracing/

dump trace:
```
#> cat trace
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
