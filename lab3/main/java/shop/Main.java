package main.java.shop;

public class Main {
    public static void main(String[] args) {

        ProductFactory bookFactory = new BookFactory();
        ProductFactory phoneFactory = new PhoneFactory();

        Product book = bookFactory.createProduct();
        Product phone = phoneFactory.createProduct();

        CartComposite cart = new CartComposite();
        cart.add(new CartItem(book));
        cart.add(new CartItem(phone));

        cart.show();
        System.out.println("Total price: " + cart.getPrice());

        OrderContext order = new OrderContext();
        order.printStatus();

        order.nextState();
        order.printStatus();

        order.nextState();
        order.printStatus();

        order.nextState();
        order.printStatus();
    }
}
