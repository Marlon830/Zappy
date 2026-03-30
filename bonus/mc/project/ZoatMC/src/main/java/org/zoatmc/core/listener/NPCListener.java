package org.zoatmc.core.listener;

import net.citizensnpcs.api.event.NPCDeathEvent;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.entity.PlayerDeathEvent;

public class NPCListener implements Listener {
    @EventHandler
    public void onDeathEvent(NPCDeathEvent event) {
        if (event.getEvent() instanceof PlayerDeathEvent playerEvent)
            playerEvent.setDeathMessage(null);
    }
}
