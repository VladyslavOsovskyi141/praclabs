package main.java.shop;

public interface OrderState {
    void next(OrderContext order);
    String getStatus();
}
