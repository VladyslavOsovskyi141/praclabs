package main.java.shop;

public class NewState implements OrderState {
    @Override
    public void next(OrderContext order) {
        order.setState(new PaidState());
    }

    @Override
    public String getStatus() {
        return "New";
    }
}
