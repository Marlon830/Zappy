package org.zoatmc.http;

import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpServer;
import org.bukkit.entity.Player;
import org.zoatmc.http.handler.ResourcePackResourceHandler;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.URI;

public class ResourceServer {
    public static final int PORT = 25587;

    public static final String RELATIVE_RESOURCE_PACK_URI = "/resources.zip";

    private final HttpServer httpServer;

    private final ResourcePackResourceHandler resourcePackResourceHandler;
    private final URI resourcePackUri;

    public ResourceServer(int port) throws IOException {
        this.httpServer = HttpServer.create(new InetSocketAddress(port), 0);

        this.resourcePackResourceHandler = new ResourcePackResourceHandler("/pack/");

        HttpContext entrypointContext = this.httpServer.createContext(ResourceServer.RELATIVE_RESOURCE_PACK_URI,
            this.resourcePackResourceHandler);

        InetSocketAddress serverAddress = this.httpServer.getAddress();
        this.resourcePackUri = URI.create("http://" + InetAddress.getLocalHost().getHostAddress() + ":" + serverAddress.getPort() + entrypointContext.getPath());
    }

    public void start() {
        this.httpServer.start();
    }

    public void stop() {
        this.httpServer.stop(0);
    }

    public ResourceServer() throws IOException {
        this(ResourceServer.PORT);
    }

    public InetSocketAddress getAddress() {
        return this.httpServer.getAddress();
    }

    public URI getResourcePackUri() {
        return this.resourcePackUri;
    }

    public byte[] getResourcePackHash() {
        return this.resourcePackResourceHandler.getHash();
    }

    public void transferResourcePack(Player player, String prompt) {
        player.setResourcePack(this.getResourcePackUri().toString(), this.getResourcePackHash(), prompt);
    }

    public void transferResourcePack(Player player) {
        player.setResourcePack(this.getResourcePackUri().toString(), this.getResourcePackHash());
    }
}
