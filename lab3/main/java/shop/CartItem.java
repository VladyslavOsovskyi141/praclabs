package main.java.shop;

public class CartItem implements CartComponent {
    private Product product;

    public CartItem(Product product) {
        this.product = product;
    }

    @Override
    public double getPrice() {
        return product.getPrice();
    }

    @Override
    public void show() {
        System.out.println(product.getName() + " : " + product.getPrice());
    }
}
