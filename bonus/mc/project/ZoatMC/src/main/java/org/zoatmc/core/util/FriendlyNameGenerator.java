package org.zoatmc.core.util;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class FriendlyNameGenerator {
    private static final Pattern FORMAT_PATTERN = Pattern.compile("\\{}");

    protected List<String> words = new ArrayList<>();
    protected String format;

    public FriendlyNameGenerator(InputStream wordInputStream, String format) {
        this.format = format;

        Scanner wordScanner = new Scanner(wordInputStream);

        while (wordScanner.hasNext())
            this.words.add(wordScanner.next());
    }

    public FriendlyNameGenerator(InputStream wordInputStream) {
        this(wordInputStream, "{}-{}");
    }

    public FriendlyNameGenerator() {
        this(FriendlyNameGenerator.class.getResourceAsStream("/text/words.txt"));
    }

    public String generate() {
        Matcher matcher = FriendlyNameGenerator.FORMAT_PATTERN.matcher(format);
        StringBuilder result = new StringBuilder();

        while (matcher.find())
            matcher.appendReplacement(result, words.get((int) (Math.random() * words.size())));
        matcher.appendTail(result);

        return result.toString();
    }
}
