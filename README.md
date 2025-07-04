# SA-MP Advanced Airdrop Event System

## 📋 Descrição

Sistema de eventos Airdrop para servidores SA-MP. Este sistema permite que administradores iniciem eventos de Airdrop em qualquer localização do mapa, criando uma zona de combate onde jogadores podem competir para coletar armas e itens especiais.


https://github.com/user-attachments/assets/7c6386d3-3db8-48d0-b650-1c4a05c3710d


## ✨ Funcionalidades

- Criação de eventos Airdrop em qualquer localização do mapa
- Animação realista de queda do Airdrop do céu
- Zona de perigo demarcada com GangZone vermelha
- Notificação para jogadores ao entrar na zona de perigo
- Recompensa de armas para o jogador que coletar o Airdrop
- Ícone no mapa para localizar o Airdrop
- Texto 3D informativo sobre o Airdrop
- Sistema de iteração eficiente para gerenciar jogadores coletando o Airdrop

## 📦 Dependências

Este sistema requer as seguintes dependências:

### Streamer Plugin v2.9.6 v1.0.0
- Download: [GitHub - samp-incognito/samp-streamer-plugin](https://github.com/samp-incognito/samp-streamer-plugin/releases)

### YSI-Includes
- Download: [GitHub - pawn-lang/YSI-Includes](https://github.com/pawn-lang/YSI-Includes)


### Pawn.CMD 3.4.0
- Download: [GitHub - katursis/Pawn.CMD](https://github.com/katursis/Pawn.CMD/releases)

## 🔧 Configuração

Você pode configurar o sistema editando os seguintes valores no início do arquivo:

```pawn
#define AIRDROP_OBJECTS_COUNT 2       // Número de objetos usados no Airdrop
static const Float:E_AIRDROP_SPEED = 2.0;  // Velocidade de queda do Airdrop
```

Para modificar a recompensa do Airdrop, edite a função `OnTimerCollectAirdrop`:

```pawn
GivePlayerWeapon(playerid, 31, 150);  // Dá ao jogador uma M4 com 150 munições
```

## 📝 Comandos

- `/Airdrop` - Inicia um evento de Airdrop na posição atual do jogador
- `/pAirdrop` - Coleta o Airdrop (deve estar próximo ao Airdrop e dentro da zona de perigo)

## 👨‍💻 Desenvolvido por

- MARINHO
- GitHub: [eykMarinho](https://github.com/eykMarinho)
- YouTube: [@eykMarinho](https://www.youtube.com/@eykMarinho)

