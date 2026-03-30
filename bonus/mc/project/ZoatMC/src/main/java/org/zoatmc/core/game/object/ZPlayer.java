package org.zoatmc.core.game.object;

import net.citizensnpcs.api.npc.NPC;
import net.citizensnpcs.trait.HologramTrait;
import net.md_5.bungee.api.chat.ComponentBuilder;
import org.bukkit.Bukkit;
import org.bukkit.Location;
import org.bukkit.Material;
import org.bukkit.entity.HumanEntity;
import org.bukkit.entity.Player;
import org.bukkit.inventory.Inventory;
import org.bukkit.inventory.ItemStack;
import org.bukkit.inventory.meta.ItemMeta;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.manager.ZControllerManager;
import org.zoatmc.core.game.runnable.ZPlayerRunnable;
import org.zoatmc.core.util.FriendlyNameGenerator;
import org.zoatmc.core.util.item.PlayerItems;

public class ZPlayer extends ZEgg {
    private static final FriendlyNameGenerator nameGenerator = new FriendlyNameGenerator(
        FriendlyNameGenerator.class.getResourceAsStream("/text/names.txt"), "{}");

    private Inventory playerInventory;
    private final ZContent inventory;
    private final String teamName;
    private int direction;
    private ZTeam team;
    private int level;

    private final ZPlayerRunnable runnable = new ZPlayerRunnable(this);
    private ZPlayerController controller = null;
    private ZParticle particle = null;
    private final String name;
    private NPC npc = null;

    public ZPlayer(ZGame game, int id, int x, int y, int direction, int level, String team) {
        super(game, id, x, y);

        this.inventory = new ZContent();
        this.direction = direction;
        this.level = level;
        this.teamName = team;
        this.team = game.getTeam(team);
        this.name = ZPlayer.nameGenerator.generate();

        this.initInventory();
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public int getDirection() {
        return direction;
    }

    public float getRotation() {
        return switch (direction) {
            case 1 -> 180;
            case 2 -> -90;
            case 3 -> 0;
            case 4 -> 90;
            default -> -1;
        };
    }

    public void setDirection(int direction) {
        this.direction = direction;
    }

    public NPC getNpc() {
        return npc;
    }

    public void setNpc(NPC npc) {
        this.npc = npc;
    }

    public ZTeam getTeam() {
        if (team == null)
            team = getGame().getTeam(teamName);
        return team;
    }

    public String getTeamName() {
        return teamName;
    }

    public ZContent getInventory() {
        return inventory;
    }

    public Inventory getPlayerInventory() {
        return playerInventory;
    }

    public Location getLocation() {
        Location loc = getGame().getMapLocation();

        return loc.clone().add(getX() * ZGame.TILE_SIZE + ZGame.TILE_SIZE / 2.0, 0,
                               getY() * ZGame.TILE_SIZE + ZGame.TILE_SIZE / 2.0);
    }

    public String getName() {
        return name;
    }

    public ZParticle getParticle() {
        return particle;
    }

    public void setParticle(ZParticle particle) {
        this.particle = particle;
    }

    public ZPlayerController getController() {
        return controller;
    }

    public void setController(ZPlayerController controller) {
        this.controller = controller;
    }

    public void start() {
        runnable.runTaskTimer(ZoatPlugin.getInstance(), 0, 1);
    }

    public void kill() {
        if (npc != null) {
            ((Player) npc.getEntity()).setHealth(0);
            Bukkit.getScheduler().runTaskLater(ZoatPlugin.getInstance(), this::remove, 30);
        }

        playerInventory.getViewers().stream().toList().forEach(HumanEntity::closeInventory);
        runnable.cancel();
    }

    public void remove() {
        if (controller != null) {
            controller.getPlayer().getInventory().clear();
            ZControllerManager.removeController(controller);
        }

        if (npc != null) {
            npc.despawn();
            npc.destroy();
            npc = null;
        }
    }

    public void update(boolean force) {
        if (npc == null || getTeam() == null)
            return;

        if (playerInventory.getHolder() == null)
            initInventory();

        HologramTrait hologramTrait = npc.getOrAddTrait(HologramTrait.class);

        String fmtLevel =
            new ComponentBuilder()
                .append("Level")
                .color(ZoatFormatter.COLOR_BASE)
                .append(" %d".formatted(level))
                .color(ZoatFormatter.COLOR_ACCENT)
                .build()
                .toLegacyText();

        if (hologramTrait.getLines().isEmpty())
            hologramTrait.addLine(fmtLevel);
        else if (!hologramTrait.getLines().getFirst().equals(fmtLevel) || force)
            hologramTrait.setLine(0, fmtLevel);

        String fmtName = team.getChatColor() + name;

        if (!npc.getName().equals(fmtName) || force)
            npc.setName(fmtName);

        if (npc.getEntity() instanceof Player ep && ep.getInventory().getChestplate() == null)
            ep.getInventory().setChestplate(team.getChestplate());

        updateInventory();
    }

    private void initInventory() {
        if (playerInventory != null)
            playerInventory.getViewers().stream().toList().forEach(HumanEntity::closeInventory);

        this.playerInventory = Bukkit.createInventory(
            npc == null ? null : (Player) npc.getEntity(), 9,
            (this.team != null ? this.team.getChatColor() : "") + this.name + "'s Inventory"
        );

        ItemStack empty = new ItemStack(Material.GRAY_STAINED_GLASS_PANE);
        ItemMeta meta = empty.getItemMeta();
        if (meta != null) {
            meta.setDisplayName(" ");
            empty.setItemMeta(meta);
        }

        playerInventory.setMaxStackSize(127);
        playerInventory.setItem(7, empty);
        playerInventory.setItem(8, PlayerItems.SPECTATE);

        int i = 0;
        for (ZContent.ResourceType type : ZContent.ResourceType.values()) {
            ItemStack item = new ItemStack(type.getMaterial(), 1);
            ItemMeta itemMeta = item.getItemMeta();

            if (itemMeta != null) {
                itemMeta.setDisplayName(type.getDisplayName());
                item.setItemMeta(itemMeta);
            }

            playerInventory.setItem(i++, item);
        }
    }

    private void updateInventory() {
        int i = 0;
        for (ZContent.ResourceType type : ZContent.ResourceType.values()) {
            ItemStack item = playerInventory.getItem(i++);
            if (item == null || item.getItemMeta() == null)
                continue;

            ItemMeta itemMeta = item.getItemMeta();
            itemMeta.setDisplayName(
                ZoatFormatter.COLOR_ACCENT.toString() + inventory.getResourceQuantity(type) + " " + type.getDisplayName());
            item.setAmount(Math.max(1, inventory.getResourceQuantity(type)));
            item.setItemMeta(itemMeta);
        }
    }

    public void spectateFrom(Player spectator) {
    }
}
