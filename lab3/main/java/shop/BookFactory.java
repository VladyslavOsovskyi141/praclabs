package main.java.shop;
public class BookFactory extends ProductFactory {
    @Override
    public Product createProduct() {
        return new Book();
    }
}
