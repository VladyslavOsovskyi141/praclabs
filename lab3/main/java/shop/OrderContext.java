package main.java.shop;

public class OrderContext {
    private OrderState state = new NewState();

    public void setState(OrderState state) {
        this.state = state;
    }

    public void nextState() {
        state.next(this);
    }

    public void printStatus() {
        System.out.println("Order status: " + state.getStatus());
    }
}
