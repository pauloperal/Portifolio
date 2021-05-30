//Paulo Ponciano Peral Filho
//pauloppfilho@hotmail.com
//34 99192 2582


package org.example;

import org.junit.Assert;
import org.junit.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.Select;

public class Pratica {
    @Test
    public void testeParaCadastrarOcorrencia(){
        WebDriver driver = new ChromeDriver();
        driver.navigate().to("https://mantis-prova.base2.com.br/");

        WebElement usernameField = driver.findElement(By.name("username")); //localizei elemento usuário
        usernameField.sendKeys("treinamento09");
        WebElement passwordField = driver.findElement(By.name("password")); //localizei a senha
        passwordField.sendKeys("123456");
        WebElement loginField = driver.findElement(By.xpath("//input[@value='Login']")); //localizei login através do xpath
        loginField.click();

        WebElement relatarCasoButton  = driver.findElement(By.linkText("Relatar Caso"));
        relatarCasoButton.click();

        Select combo = new Select(driver.findElement(By.name("category_id")));
        combo.selectByValue("65");

        combo = new Select(driver.findElement(By.name("reproducibility")));
        combo.selectByValue("30");

        combo = new Select(driver.findElement(By.name("severity")));
        combo.selectByValue("20");

       WebElement resumo = driver.findElement(By.name("summary"));
       resumo.sendKeys("Processo Seletivo Base2");

       WebElement descricao = driver.findElement(By.name("description"));
       descricao.sendKeys("Teste automatizado feito por Paulo Ponciano Peral Filho com objetivo de " +
                "ser aprovado no processo da Base2!");

       WebElement passoAPasso = driver.findElement(By.name("steps_to_reproduce"));
       passoAPasso.sendKeys("1 - Aprender Selenium" +
               "2 - Se dedicar muito e estudar" +
               "3 - Ser aprovado!");

       WebElement sendButton = driver.findElement(By.xpath("//td[@class='center']/input[@value='Enviar Relatório']"));
       sendButton.click();


       //Aqui foi usado o getPageSource para que eu pegasse o código HTML e localizasse o div correspondente.
       //String source = driver.getPageSource();
       //System.out.println(source);

       WebElement operacaoRealizada = driver.findElement(By.xpath("//div[@align='center']"));
       String teste = operacaoRealizada.getText().substring(0,31);
       Assert.assertEquals("Operação realizada com sucesso.", teste);

        //Caso tenha havido erro nesta parte, a ocorrência não foi realizada,
        //portanto o caso de teste parará aqui;


        //Caso a ocorrência seja realizada, vamos verificar se os dados foram inclusos.
        //Não é ideal fazer dois asserts no mesmo código, mas também, como dito no curso
        //não é ideal criar um teste que dependa do outro.
        //Então criarei o assert de verificação de dados dentro deste teste.

        //Na ultima linha do desafio temos pedindo para verificar se a ocorrência foi salva com os dados informados
        //Nestes testes, acesso a ultima ocorrência criada (tenho garantia que foi criada pois passou no assert acima)
        //e faço a verificação das informações.


        WebElement minhaVisao = driver.findElement(By.linkText("Minha Visão"));
        minhaVisao.click();

        WebElement ultimoCriado = driver.findElement(By.xpath("//span[@class='small']/a[@title='[novo] Processo Seletivo Base2']"));
        ultimoCriado.click();

        //Verifica Categoria
        WebElement categoriaTeste = driver.findElement(By.xpath("//tr[@class='row-1']/td[text()='[Todos os Projetos] 7EI2PODHPN']"));
        String categoriaTesteString = categoriaTeste.getText().substring(20,30);
        Assert.assertEquals("7EI2PODHPN", categoriaTesteString);

        //Verifica Frequencia
        WebElement frequenciaTeste = driver.findElement(By.xpath("//tr[@class='row-2']/td[text()='às vezes']"));
        String frequenciaTesteString = frequenciaTeste.getText();
        Assert.assertEquals("às vezes", frequenciaTesteString);

        //Verifica Gravidade
        WebElement gravidadeTeste = driver.findElement(By.xpath("//tr[@class='row-2']/td[text()='trivial']"));
        String gravidadeTesteString = gravidadeTeste.getText();
        Assert.assertEquals("trivial", gravidadeTesteString);

        //Verifica descricao
        WebElement descricaoTeste = driver.findElement(By.xpath("//tr[@class='row-2']/td[text()='Teste automatizado feito por Paulo Ponciano Peral Filho com objetivo de ser aprovado no processo da Base2!']"));
        String descricaoTesteString = descricaoTeste.getText();
        Assert.assertEquals("Teste automatizado feito por Paulo Ponciano Peral Filho com objetivo de ser aprovado no processo da Base2!", descricaoTesteString);

        //Verifica passoApasso
        WebElement passoApassoTeste = driver.findElement(By.xpath("//tr[@class='row-1']/td[text()='1 - Aprender Selenium2 - Se dedicar muito e estudar3 - Ser aprovado!']"));
        String passoApassoTesteString = passoApassoTeste.getText();
        Assert.assertEquals("1 - Aprender Selenium2 - Se dedicar muito e estudar3 - Ser aprovado!", passoApassoTesteString);
        driver.quit();
    }
}