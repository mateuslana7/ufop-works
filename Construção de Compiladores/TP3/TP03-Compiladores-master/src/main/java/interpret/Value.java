package interpret;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

public class Value {
   @Override
   public String toString() {
      return ToStringBuilder.reflectionToString(
         this,
         ToStringStyle.SHORT_PREFIX_STYLE);
   }

}
