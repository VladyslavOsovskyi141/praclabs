package main.java.shop;
public class Book implements Product {
    @Override
    public String getName() {
        return "Book";
    }

    @Override
    public double getPrice() {
        return 300;
    }
}
