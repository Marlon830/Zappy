package org.zoatmc.core.game.event;

import org.zoatmc.core.ZoatPlugin;

import java.lang.annotation.Annotation;
import java.lang.reflect.Method;
import java.util.*;
import java.util.logging.Level;

record ZEventListenerRecord(
    ZEventListener listener,
    Method method
) {}

public class ZEventBus {
    private final Map<Class<? extends ZEvent>, List<ZEventListenerRecord>> listeners = new HashMap<>();
    private final Queue<ZEvent> eventQueue = new LinkedList<>();

    protected void registerHandler(ZEventListener listener, Class<? extends ZEvent> targetEventType, Method method)
    {
        ZEventListenerRecord record = new ZEventListenerRecord(listener, method);

        if (this.listeners.containsKey(targetEventType))
            this.listeners.get(targetEventType).add(record);
        else
            this.listeners.put(targetEventType, List.of(record));
    }

    public void registerListener(ZEventListener listener) {
        for (Method method : listener.getClass()
                                     .getDeclaredMethods()) {
            Annotation[] annotations = method.getAnnotationsByType(ZEventHandler.class);

            if (annotations.length == 0)
                continue;
            if (annotations.length > 1)
                throw new IllegalArgumentException(
                    "Method '%s' has more than one ZEventHandler annotation.".formatted(method.getName()));

            if (!(
                method.getReturnType().equals(Void.TYPE) &&
                method.getParameterCount() == 1 &&
                ZEvent.class.isAssignableFrom(method.getParameterTypes()[0])
            ))
                throw new IllegalArgumentException(
                    "Method '%s' does not have the correct signature.".formatted(method.getName()));

            Class<? extends ZEvent> targetEventType = method.getParameterTypes()[0].asSubclass(ZEvent.class);
            this.registerHandler(listener, targetEventType, method);
        }
    }

    public void unregisterListener(ZEventListener listener) {
        for (List<ZEventListenerRecord> records : this.listeners.values()) {
            records.removeIf(record -> record.method()
                                             .getDeclaringClass()
                                             .equals(listener.getClass()));
        }
    }

    public void postEvent(ZEvent event) {
        synchronized (this.eventQueue) {
            this.eventQueue.add(event);
        }
    }

    protected void propagateEvent(ZEvent event) {
        Class<? extends ZEvent> eventType = event.getClass();

        if (!this.listeners.containsKey(eventType))
            return;

        List<ZEventListenerRecord> methods = this.listeners.get(eventType);

        for (ZEventListenerRecord record : methods) {
            try {
                record.method().invoke(record.listener(), event);
            } catch (Exception e) {
                ZoatPlugin
                    .getInstance()
                    .getLogger()
                    .log(Level.WARNING,
                            "Failure to invoke event handler '%s' for event '%s' on class '%s'.".formatted(record.method().getName(), event.getClass().getName(), record.method().getDeclaringClass().getName()),
                            e.fillInStackTrace());
            }
        }
    }

    public void processEvents() {
        synchronized (this.eventQueue) {
            while (!this.eventQueue.isEmpty()) {
                ZEvent event = this.eventQueue.poll();
                this.propagateEvent(event);
            }
        }
    }
}
