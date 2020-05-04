from django.urls import path
from . import views

#app_name = 'articles'
#app_name = 'app'

urlpatterns = [
    path('', views.index, name='index'),
    path('detalhesFonte', views.detalhesFonte, name='detalhesFonte'),
    path('detalhesLana', views.detalhesLana, name='detalhesLana'),
    path('detalhesThiago', views.detalhesThiago, name='detalhesThiago'),
    #path('', views.app_list, name="list"),
    #path('cadastro', views.cadastro, name='cadastro'),
    #path('accounts/', include('django.contrib.auth.urls')),
]