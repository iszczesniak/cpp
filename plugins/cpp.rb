module Jekyll
  module Tags
    class CppTag < Liquid::Tag

      def initialize(tag_name, markup, token)
        super
        @fn = markup
      end

      def render(context)
        str = "{% highlight C++ linenos %}{% include_relative " + @fn + " %}{% endhighlight %}"
        Liquid::Template.parse(str).render(context)
      end
    end
  end
end

Liquid::Template.register_tag('cpp', Jekyll::Tags::CppTag)
