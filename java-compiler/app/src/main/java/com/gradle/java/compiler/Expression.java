package com.gradle.java.compiler;

abstract class Expression {
    Expression left;
    Token operator;
    Expression right;
        
    static class Binary extends Expression {
        Binary(Expression left, Token operator, Expression right) {
            this.left = left;
            this.operator = operator;
            this.right = right;
        }
    }

}
