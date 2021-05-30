package org.example;

import org.junit.Assert;
import org.junit.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedCondition;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

public class ExemplosSelenium {
    @Test
    public void helloWorld(){ //Abrir o browser, e tentar navegar pro site do google
        WebDriver driver = new ChromeDriver(); //Cria o objeto driver
        driver.navigate().to("http://google.com"); //navega para o google
        Assert.assertEquals("Google", driver.getTitle()); //getTitle verifica o título
        driver.quit();
    }

    //Acessar o sistema Mantis
    //Preencher usuário
    //Preencher senha
    //Clicar em login
    //Usuário autenticado com sucesso
    @Test
    public void efetuarLoginComSucesso(){
        WebDriver driver = new ChromeDriver();
        driver.navigate().to("https://mantis-prova.base2.com.br/");

        WebElement usernameField = driver.findElement(By.name("username")); //localizei elemento usuário
        usernameField.sendKeys("treinamento01");
        WebElement passwordField = driver.findElement(By.name("password")); //localizei a senha
        passwordField.sendKeys("123456");
        WebElement loginField = driver.findElement(By.xpath("//input[@value='Login']")); //localizei login através do xpath
        loginField.click();

        String usuarioLogadoText = driver.findElement(By.xpath("//td[@class='login-info-left']/span[@class='italic']")).getText();
        Assert.assertEquals("Treinamento01", usuarioLogadoText);
        driver.quit();
    }

    @Test
    public void exemploSincronizacao(){
        WebDriver driver = new ChromeDriver();
        driver.manage().window().maximize();
        driver.navigate().to("http://blackmirror.crowdtest.me.s3-website-us-east-1.amazonaws.com/register/device");


        WebElement nextButton  = driver.findElement(By.linkText("Prosseguir"));
        nextButton.click();
        WebElement emailField = driver.findElement(By.id("login"));
        WebElement passwordField = driver.findElement(By.id("password"));
        WebElement entrarButtonField = driver.findElement(By.xpath("//button[text()='ENTRAR']"));

        emailField.sendKeys("paulo@paulo.com");
        passwordField.sendKeys("123456");
        entrarButtonField.click();

        WebDriverWait wait = new WebDriverWait(driver, 10);
        //espera o elemento existir
        wait.until(ExpectedConditions.presenceOfAllElementsLocatedBy(By.xpath("//p[@class='login-error']/span[@class='error-msg']")));
        //instancio
        WebElement  erroText = driver.findElement(By.xpath("//p[@class='login-error']/span[@class='error-msg']"));
        //espero ser visivel
        wait.until(ExpectedConditions.visibilityOf(erroText));
        //aqui faço interação
        String erroExibido = erroText.getText();

        Assert.assertEquals("E-mail ou senha inválidos.", erroExibido);
        driver.quit();

    }
}
