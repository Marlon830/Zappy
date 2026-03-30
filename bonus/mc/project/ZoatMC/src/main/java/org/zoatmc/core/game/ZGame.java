package org.zoatmc.core.game;

import org.bukkit.Location;
import org.bukkit.entity.Player;
import org.joml.Vector2i;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.event.ZEventBus;
import org.zoatmc.core.game.listener.ZGameEggListener;
import org.zoatmc.core.game.listener.ZGameListener;
import org.zoatmc.core.game.listener.ZGameMapListener;
import org.zoatmc.core.game.listener.ZGamePlayerListener;
import org.zoatmc.core.game.manager.ZGameManager;
import org.zoatmc.core.game.manager.ZTeamManager;
import org.zoatmc.core.game.object.*;
import org.zoatmc.core.game.protocol.watcher.ZWatcherClient;
import org.zoatmc.core.game.runnable.ZGameRunnable;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class ZGame {
    public static final int TILE_SIZE = 3;

    private final Location mapLocation;
    private ZMap map;
    private final List<ZPlayer> players;
    private final List<ZEgg> eggs;
    private final List<ZPlayerController> pendingControllers = new ArrayList<>();
    private final String name;

    private final ZEventBus eventBus = new ZEventBus();
    private final ZWatcherClient client;

    private final ZGameRunnable runnable;

    private final ZTeamManager teamManager = new ZTeamManager();

    public ZGame(Location mapLocation, String host, int port) throws IOException {
        this.client = new ZWatcherClient(this, host, port);
        this.mapLocation = mapLocation;

        this.map = null;
        this.players = new ArrayList<>();
        this.eggs = new ArrayList<>();
        this.name = ZGameManager.addGame(this);

        this.runnable = new ZGameRunnable(this);
        this.registerListeners();
    }

    private void registerListeners() {
        this.eventBus.registerListener(new ZGameMapListener());
        this.eventBus.registerListener(new ZGameListener());
        this.eventBus.registerListener(new ZGameEggListener());
        this.eventBus.registerListener(new ZGamePlayerListener());
    }

    public void close() throws IOException {
        this.client.close();

        if (this.map != null)
            this.map.clear();

        this.runnable.cancel();

        players.forEach(ZPlayer::remove);
    }

    public synchronized ZEventBus getEventBus() {
        return this.eventBus;
    }

    public synchronized ZMap getMap() {
        return map;
    }

    public synchronized void setMap(ZMap map) {
        this.map = map;
    }

    public synchronized List<ZEgg> getEggs() {
        return this.eggs;
    }

    public synchronized List<ZPlayer> getPlayers() {
        return this.players;
    }

    public synchronized List<ZPlayer> getPlayers(Vector2i position) {
        return this.players.stream()
                           .filter(player -> player.getX() == position.x && player.getY() == position.y)
                           .toList();
    }

    public synchronized List<ZPlayer> getPlayers(ZTeam team) {
        return this.players.stream()
                           .filter(player -> player.getTeam().equals(team))
                           .toList();
    }

    public synchronized ZPlayer getPlayer(int id) {
        return this.players.stream()
                           .filter(player -> player.getId() == id)
                           .findFirst()
                           .orElse(null);
    }

    public ZEgg getEgg(int eggId) {
        return this.eggs.stream()
                .filter(egg -> egg.getId() == eggId)
                .findFirst()
                .orElse(null);
    }

    public synchronized void addPlayer(ZPlayer player) {
        this.players.add(player);
    }

    public synchronized void removePlayer(ZPlayer player) {
        this.players.remove(player);
    }

    public synchronized void addEgg(ZEgg egg) {
        this.eggs.add(egg);
    }

    public synchronized void removeEgg(ZEgg egg) {
        this.eggs.remove(egg);
    }

    public synchronized Location getMapLocation() {
        return this.mapLocation;
    }

    public synchronized String getHost() {
        return this.client.getAddress().getHostName();
    }

    public synchronized int getPort() {
        return this.client.getAddress().getPort();
    }

    public String getName() {
        return name;
    }

    public ZTeam getTeam(String name) {
        return this.teamManager.getTeam(name);
    }

    public HashMap<String, ZTeam> getTeams() {
        return this.teamManager.getTeams();
    }

    public void addTeam(String name) {
        this.teamManager.addTeam(name);
    }

    public void addPlayerController(Player player, ZTeam team) {
        ZPlayerController playerController = new ZPlayerController(this, team, player);
        if (playerController.getHandler() == null) {
            player.spigot().sendMessage(ZoatFormatter.error("Failed to connect with the remote game server."));
            return;
        }

        this.pendingControllers.add(playerController);
    }

    public ZPlayerController getPlayerController() {
        if (this.pendingControllers.isEmpty())
            return null;
        return this.pendingControllers.removeFirst();
    }
}
