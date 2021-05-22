import br.com.alura.tdd.modelo.Funcionario;
import br.com.alura.tdd.service.BonusService;
import org.junit.Assert;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.LocalDate;

/** 
* BonusService Tester. 
* 
* @author <Paulo Peral>
* @since <pre>mai 18, 2021</pre> 
* @version 1.0 
*/ 
public class BonusServiceTest { 

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
}

    BonusService bonusService = new BonusService();
    @Test
public void TestarBonusDeFuncionarioComSalarioMenorQueDezMil() throws Exception {
    Funcionario funcionario = new Funcionario("Paulo", LocalDate.of(2021,07,15),
                                                    BigDecimal.valueOf(2000));

    BigDecimal teste = funcionario.getSalario().multiply(new BigDecimal(0.1)).setScale(2, RoundingMode.HALF_UP);
    BigDecimal valor = bonusService.calcularBonus(funcionario);
        Assert.assertEquals(teste,valor);
}
    @Test
    public void TestarBonusDeFuncionarioComSalarioMaiorQueDezMil() throws Exception {
        Funcionario funcionario = new Funcionario("Paulo", LocalDate.of(2021,07,15),
                BigDecimal.valueOf(12000));
        BigDecimal valor = bonusService.calcularBonus(funcionario);
        Assert.assertEquals(BigDecimal.ZERO.setScale(2, RoundingMode.HALF_UP),valor);
    }
    @Test
    public void TestarBonusDeFuncionarioComSalarioIgualADezMil() throws Exception {
        Funcionario funcionario = new Funcionario("Paulo", LocalDate.of(2021,07,15),
                BigDecimal.valueOf(10000));
        BigDecimal valor = bonusService.calcularBonus(funcionario);
        Assert.assertEquals(BigDecimal.valueOf(1000).setScale(2, RoundingMode.HALF_UP),valor);
    }

} 
