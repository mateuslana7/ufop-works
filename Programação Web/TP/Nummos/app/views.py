from django.shortcuts import render
from django.utils import timezone

from .models import Post
# Create your views here.
def index(request):
    posts = Post.objects.filter(published_date__lte=timezone.now()).order_by('published_date') 
    return render(request, 'index.html', {'posts': posts})

def detalhesFonte(request):
	return render(request, 'detalhesFonte.html', {})

def detalhesLana(request):
	return render(request, 'detalhesLana.html', {})

def detalhesThiago(request):
	return render(request, 'detalhesThiago.html', {})

#def article_list(request):
#	articles = Article.objects.all().order_by('date');
#	return render(request, 'articles/article_list.html',{'articles': articles})
