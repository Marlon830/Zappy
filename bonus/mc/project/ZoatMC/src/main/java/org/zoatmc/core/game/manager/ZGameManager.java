package org.zoatmc.core.game.manager;

import net.citizensnpcs.api.npc.NPC;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.util.FriendlyNameGenerator;

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.logging.Level;

public class ZGameManager {
    private static final FriendlyNameGenerator nameGenerator = new FriendlyNameGenerator();

    private static final Map<String, ZGame> games = new HashMap<>();

    public static void addGame(String name, ZGame game) {
        ZGameManager.games.put(name, game);
    }

    public static synchronized String addGame(ZGame game) {
        String name = ZGameManager.nameGenerator.generate();

        ZGameManager.addGame(name, game);

        return name;
    }

    public static synchronized void removeGame(String name) throws IOException {
        ZGame game = ZGameManager.games.remove(name);
        game.close();
    }

    public static synchronized void removeGame(ZGame game) throws IOException {
        Iterator<Map.Entry<String, ZGame>> iterator = ZGameManager.games.entrySet().iterator();

        while (iterator.hasNext()) {
            Map.Entry<String, ZGame> entry = iterator.next();

            if (entry.getValue().equals(game)) {
                game.close();
                iterator.remove();
                break;
            }
        }
    }

    public static boolean hasGame(String gameName) {
        return ZGameManager.games.containsKey(gameName);
    }

    public static synchronized ZGame getGame(String name) {
        return ZGameManager.games.get(name);
    }

    public static synchronized ZPlayer getPlayerByNPC(NPC npc) {
        if (npc == null)
            return null;

        return games.values().stream()
                .flatMap(game -> game.getPlayers().stream())
                .filter(player -> player.getNpc().equals(npc))
                .findFirst()
                .orElse(null);
    }

    public static synchronized Map<String, ZGame> getGames() {
        return ZGameManager.games;
    }

    public static synchronized void clear() {
        Iterator<Map.Entry<String, ZGame>> iterator = ZGameManager.games.entrySet().iterator();

        while (iterator.hasNext()) {
            Map.Entry<String, ZGame> entry = iterator.next();

            try {
                entry.getValue().close();
            } catch (IOException e) {
                ZoatPlugin.getInstance()
                          .getLogger()
                          .log(Level.WARNING, "Failed to close game '%s'".formatted(entry.getKey()), e.fillInStackTrace());
            }

            iterator.remove();
        }

        ZGameManager.games.clear();
    }
}