package org.zoatmc.http.handler;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.file.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.stream.Stream;
import java.util.zip.Deflater;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class ResourcePackResourceHandler implements HttpHandler {
    protected byte[] resourcePackData;
    protected byte[] resourcePackHash;

    public ResourcePackResourceHandler(String treeLocation) {
        ByteArrayOutputStream byteOutputStream = new ByteArrayOutputStream();
        ZipOutputStream zipOutputStream = new ZipOutputStream(byteOutputStream);

        zipOutputStream.setMethod(ZipOutputStream.DEFLATED);
        zipOutputStream.setLevel(Deflater.NO_COMPRESSION);

        URL jarUrl = ResourcePackResourceHandler.class.getProtectionDomain().getCodeSource().getLocation();
        Path jarPath = Paths.get(jarUrl.getPath().replaceFirst("file:", ""));

        try (FileSystem jarFS = FileSystems.newFileSystem(jarPath, (ClassLoader) null);
             Stream<Path> directoryStream = Files.walk(jarFS.getPath(treeLocation))) {
            directoryStream.forEach(path -> {
                if (Files.isDirectory(path))
                    return;

                try {
                    zipOutputStream.putNextEntry(new ZipEntry(path.toString().replaceFirst(treeLocation, "")));
                    zipOutputStream.write(Files.readAllBytes(path));
                    zipOutputStream.closeEntry();
                } catch (IOException e) {
                    throw new RuntimeException("Failed to create zip entry '" + path.toString() + "'", e);
                }
            });

            zipOutputStream.flush();
            zipOutputStream.close();
            byteOutputStream.close();
        } catch (IOException e) {
            throw new RuntimeException("Failed to obtain a jar container filesystem stream", e);
        }

        this.resourcePackData = byteOutputStream.toByteArray();

        try {
            MessageDigest shaDigest = MessageDigest.getInstance("SHA-1");

            shaDigest.reset();
            shaDigest.update(this.resourcePackData);
            this.resourcePackHash = shaDigest.digest();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Failed to look-up SHA-1 digest class instance", e);
        }
    }

    @Override
    public void handle(HttpExchange httpExchange) throws IOException {
        httpExchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, this.resourcePackData.length);

        OutputStream responseBody = httpExchange.getResponseBody();
        responseBody.write(this.resourcePackData);
        responseBody.flush();

        httpExchange.close();
    }

    public byte[] getHash() {
        return this.resourcePackHash;
    }
}